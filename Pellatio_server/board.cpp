#include "board.h"

#ifdef WITH_TESTBOARD
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#endif

Board::Board()
{
}

void Board::initializeEmptyBoard()
{
    m_fields.clear();
    m_pieces.clear();

    for (int i = 0; i < PellatioDefinitions::BOARD_SIZE * PellatioDefinitions::BOARD_SIZE; ++i) {
        m_fields << Field(i);
    }
}

void Board::initializeStartBoard()
{
    initializeEmptyBoard();

    // Aggressoren
    for (int i = 0; i < 5; ++i) {
        int yr = 2;
        int yb = 6;
        int x = 2*i;

        Piece r("", PellatioDefinitions::Red, PellatioDefinitions::Aggressor, PellatioDefinitions::South, BoardData::indexForXandY(x, yr));
        Piece b("", PellatioDefinitions::Black, PellatioDefinitions::Aggressor, PellatioDefinitions::North, BoardData::indexForXandY(x, yb));
        r.generateId();
        b.generateId();

        m_pieces[r.id()] = r;
        m_pieces[b.id()] = b;
    }

    // Phalangiten
    for (int i = 0; i < 4; ++i) {
        int yr = 1;
        int yb = 7;
        int x = 1+2*i;

        Piece r("", PellatioDefinitions::Red, PellatioDefinitions::Phalangit, PellatioDefinitions::South, BoardData::indexForXandY(x, yr));
        Piece b("", PellatioDefinitions::Black, PellatioDefinitions::Phalangit, PellatioDefinitions::North, BoardData::indexForXandY(x, yb));
        r.generateId();
        b.generateId();

        m_pieces[r.id()] = r;
        m_pieces[b.id()] = b;
    }

    // Kavaleristen / General
    for (int i = 0; i < 3; ++i) {
        int yr = 0;
        int yb = 8;
        int x = 2+2*i;
        PellatioDefinitions::PieceType t = (i == 1) ? PellatioDefinitions::General : PellatioDefinitions::Kavalerist;

        Piece r("", PellatioDefinitions::Red, t, PellatioDefinitions::South, BoardData::indexForXandY(x, yr));
        Piece b("", PellatioDefinitions::Black, t, PellatioDefinitions::North, BoardData::indexForXandY(x, yb));
        r.generateId();
        b.generateId();

        m_pieces[r.id()] = r;
        m_pieces[b.id()] = b;
    }

    foreach (QString id, m_pieces.keys()) {
        placePiece(&m_pieces[id], &m_fields[m_pieces[id].field()]);
    }

}

#ifdef WITH_TESTBOARD
void Board::initializeTestBoard(QString boardFile)
{
    initializeEmptyBoard();
    QFile f(boardFile);
    if (!f.open(QIODevice::ReadOnly)) {
        qCritical() << "Cannot open" << boardFile;
        return;
    }
    QTextStream ts(&f);
    QString boardStr = ts.readAll();
    f.close();


    QStringList lines = boardStr.split("\n");
    lines.replaceInStrings("\r", "");
    if (lines.size() > 9) {
        // Special case: If 10 lines, and last is empty, no warning
        if (!(lines.size() == 10 && lines[9].trimmed().isEmpty())) {
            qWarning() << "Boardfile has more than 9 lines. Additional Lines are ignored";
        }
        lines.erase(lines.begin()+9, lines.end());
    }

    QRegExp rxPiece("([rb])([APKG])(\\d)?");
    for (int r = 0; r < lines.size(); ++r) {
        QStringList parts = lines[r].split("\t");
        if (parts.size() > 9) {
            qWarning() << "Line" << (r+1) << "has more than 9 Fields. Additional Fields are ignored";
            parts.erase(parts.begin()+9, parts.end());
        }

        for (int c = 0; c < parts.size(); ++c) {
            if (parts[c].isEmpty()) continue;
            if (!rxPiece.exactMatch(parts[c])) {
                qWarning() << "Cannot parse" << parts[c] << "(Line" << r << ", Field" << c <<")";
                continue;
            }

            QChar clr = rxPiece.cap(1)[0];
            QChar typ = rxPiece.cap(2)[0];
            int dir = 0;
            if (rxPiece.captureCount() > 2) {
                dir = rxPiece.cap(3).toInt();
            }

            PellatioDefinitions::Color color = (clr == 'r') ? PellatioDefinitions::Red : PellatioDefinitions::Black;
            PellatioDefinitions::PieceType pieceType;
            switch (typ.unicode()) {
            case 'A': pieceType = PellatioDefinitions::Aggressor; break;
            case 'P': pieceType = PellatioDefinitions::Phalangit; break;
            case 'K': pieceType = PellatioDefinitions::Kavalerist; break;
            case 'G': pieceType = PellatioDefinitions::General; break;
            }
            PellatioDefinitions::Direction direction = static_cast<PellatioDefinitions::Direction> (dir%8);

            Piece p("", color, pieceType, direction, BoardData::indexForXandY(c, r));
            p.generateId();

            m_pieces[p.id()] = p;
        }
    }

    foreach (QString id, m_pieces.keys()) {
        placePiece(&m_pieces[id], &m_fields[m_pieces[id].field()]);
    }
}
#endif

BoardData Board::toData() const
{
    QList<PieceData> pieces;
    foreach (const Piece &p, m_pieces) {
        pieces << PieceData(p);
    }

    BoardData ret;
    ret.setPieces(pieces);
    return ret;
}

QList<FieldData> Board::getFieldData() const
{
    QList<FieldData> fields;
    foreach (const Field &f, m_fields) {
        fields << FieldData(f);
    }
    return fields;
}

Piece Board::getPiece(QString id) const
{
    if (m_pieces.contains(id)) {
        return m_pieces[id];
    }
    return Piece();
}

void Board::updatePiece(Piece p)
{
    if (p.isValid()) {
        if (m_pieces.contains(p.id())) {
            m_fields[m_pieces[p.id()].field()].unplacePiece();
            m_pieces[p.id()] = p;
            if (p.field() >= 0)
                placePiece(&m_pieces[p.id()], &m_fields[p.field()]);
        }
    }
}

const Field *Board::field(int idx) const
{
    return &m_fields[idx];
}

void Board::resetFieldStates()
{
    for (int i = 0; i < m_fields.size(); ++i) {
        m_fields[i].setMovable(false);
        m_fields[i].setSelectable(false);
        m_fields[i].setSelected(false);
        m_fields[i].setParade(false);
    }
}

void Board::placePiece(Piece *p, Field *f)
{
    if (p && f) {
        f->placePiece(*p);
        p->setField(f->index());
    }
}

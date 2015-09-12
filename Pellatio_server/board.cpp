#include "board.h"

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

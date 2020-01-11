#include "stroke.h"

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Stroke::Stroke() : Stroke(QString::null, QPen()){}
Stroke::Stroke(const QString name, Qt::PenStyle style, const StrokePosition strokePosition ) : Stroke(name, QPen(style), strokePosition){}
Stroke::Stroke(const QString name, const QColor &color, const StrokePosition strokePosition ) : Stroke(name, QBrush(color), 1, strokePosition, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin){}
Stroke::Stroke(const QString name, const QBrush &brush, qreal width, const StrokePosition strokePosition , Qt::PenStyle style, Qt::PenCapStyle cap, Qt::PenJoinStyle join) : QPen(brush, width, style, cap, join), AbstractItemProperty(name){
   setStrokePosition(strokePosition);
   setMiterLimit(0);
}
Stroke::Stroke(const QString name, const QPen &pen, const StrokePosition strokePosition ) : QPen(pen), AbstractItemProperty(name){
    setStrokePosition(strokePosition);
    setMiterLimit(0);
}

/*!
 * \brief Assigns the given stroke to this stroke and returns a reference to this stroke.
 * \param other
 */
Stroke::Stroke(const Stroke &other) : QPen(other), AbstractItemProperty(other)
{
    m_strokePosition = other.m_strokePosition;
}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Stroke::setStrokePosition(StrokePosition position)
{
    m_strokePosition = position;
}

Stroke::StrokePosition Stroke::strokePosition() const
{
    return m_strokePosition;
}

void Stroke::fromObject(AbstractItemProperty object, QPen pen)
{
    m_id = object.m_id;
    m_isOn = object.m_isOn;
    m_blendMode = object.m_blendMode;
    m_name = object.m_name;

    setBrush(pen.brush());
//    setColor(pen.color());
//    setStyle(pen.style());
    setWidthF(pen.widthF());
    setCapStyle(pen.capStyle());
    setCosmetic(pen.isCosmetic());
    setJoinStyle(pen.joinStyle());
    setDashOffset(pen.dashOffset());
    setMiterLimit(pen.miterLimit());
    setDashPattern(pen.dashPattern());
}


/***************************************************
 *
 * Operator
 *
 ***************************************************/


bool Stroke::operator==(const Stroke &other) const
{
    if(this == &other) return true;

    return m_strokePosition == other.m_strokePosition &&
            AbstractItemProperty::operator==(other) &&
            QPen::operator==(other);

}


QDebug operator<<(QDebug dbg, const Stroke &obj)
{
    const AbstractItemProperty &aip = obj;
    const QPen &p = obj;

    dbg << "Stroke(" <<
           aip <<
           (int)obj.strokePosition() <<
           p <<
           ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Stroke &obj)
{
    const AbstractItemProperty &aip = obj;
    const QPen &p = obj;

    out << aip
        << (int)obj.strokePosition()
        << p;

    return out;
}

QDataStream &operator>>(QDataStream &in, Stroke &obj)
{
    AbstractItemProperty m_aip;
    QPen pen;
    int strokePos;

    in >> m_aip;
    in >> strokePos;
    in >> pen;

    obj.fromObject(m_aip, pen);
    obj.setStrokePosition(Stroke::StrokePosition(strokePos));

    return in;
}
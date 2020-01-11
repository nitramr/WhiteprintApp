#include "fills.h"
#include <QDebug>
#include <QLinearGradient>

/***************************************************
 *
 * Constructor
 *
 ***************************************************/

Fills::Fills() : Fills(QString::null){}

Fills::Fills(const QString name) : Fills(name, Color()){}

Fills::Fills(const QString name, const Color &color) : AbstractItemProperty(name){
    m_gradient = Gradient();
    setColor(color);
    m_fillMode = FillMode::Fill;
}

Fills::Fills(const QString name, const QPixmap &pixmap, const FillMode fillMode) :  Fills(name, Color()){
    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const QImage &image, const FillMode fillMode) : Fills(name, Color()){

    QPixmap pixmap(image.size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.drawImage(0,0,image);
    painter.end();

    setPixmap(pixmap);
    m_fillMode = fillMode;
}

Fills::Fills(const QString name, const Gradient &gradient) : Fills(name, Color()){
    setGradient(gradient);
}

Fills::Fills(const Fills &other) : AbstractItemProperty(other)
{      
    m_fillType = other.m_fillType;
    m_fillMode = other.m_fillMode;
    m_gradient = other.m_gradient;
    m_color = other.m_color;
    m_pixmap = other.m_pixmap;
    m_opacity = other.m_opacity;

}


/***************************************************
 *
 * Properties
 *
 ***************************************************/

void Fills::setFillType(FillType filltype)
{
    m_fillType = filltype;
}

FillType Fills::fillType() const
{
    return m_fillType;
}

void Fills::setFillMode(FillMode fillMode)
{
    m_fillMode = fillMode;
}

Fills::FillMode Fills::fillMode() const
{
    return m_fillMode;
}

void Fills::setGradient(Gradient gradient)
{
    m_gradient = gradient;
    setFillType(m_gradient.type());
}

Gradient Fills::gradient() const
{
    return m_gradient;
}

void Fills::setColor(Color color)
{
    int opacity = qRound(color.alpha() / 2.56);
    setOpacity(opacity);

    if(color.alpha() < 255) color.setAlpha(255);

    m_color = color;

    setFillType(FillType::Color);
}

Color Fills::color() const
{
    return m_color;
}

void Fills::setPixmap(QPixmap pixmap)
{
    m_pixmap = pixmap;
    setFillType(FillType::Image);
}

QPixmap Fills::pixmap() const
{
    return m_pixmap;
}

void Fills::setOpacity(int opacity)
{
    opacity = qMax(0, qMin(100, opacity)); //clamp values
    m_opacity = opacity;
}

int Fills::opacity() const
{
    return m_opacity;
}

void Fills::fromObject(AbstractItemProperty object)
{
    m_id = object.m_id;
    m_isOn = object.m_isOn;
    m_blendMode = object.m_blendMode;
    m_name = object.m_name;
}

/***************************************************
 *
 * Operator
 *
 ***************************************************/

bool Fills::operator==(const Fills &other) const
{
    return  m_fillType == other.m_fillType &&
            m_fillMode == other.m_fillMode &&
            m_gradient == other.m_gradient &&
            m_color == other.m_color &&
            m_pixmap.toImage() == other.m_pixmap.toImage() &&
            m_opacity == other.m_opacity &&
            AbstractItemProperty::operator==(other);
}

QDebug operator<<(QDebug dbg, const Fills &obj)
{
    const AbstractItemProperty &aip = obj;

    dbg << "Fills(" <<
           aip <<
           (int)obj.fillType() <<
           (int)obj.fillMode() <<
           obj.gradient() <<
           obj.color() <<
           obj.pixmap() <<
           obj.opacity() <<
           ")";
    return dbg.maybeSpace();
}

QDataStream &operator<<(QDataStream &out, const Fills &obj)
{
    const AbstractItemProperty &aip = obj;

    out << aip
        << (int)obj.fillType()
        << (int)obj.fillMode()
        << obj.color()
        << obj.pixmap()
        << obj.opacity()
        << obj.gradient();

    return out;
}

QDataStream &operator>>(QDataStream &in, Fills &obj)
{
    AbstractItemProperty aip;
    Color color;
    Gradient gradient;
    QPixmap pixmap;
    int opacity;
    int fillMode;
    int fillType;


    in >> aip >> fillType >> fillMode >> color >> pixmap >> opacity >> gradient;

    obj.fromObject(aip);
    obj.m_color = color;
    obj.m_opacity = opacity;
    obj.m_pixmap = pixmap;
    obj.m_fillMode = Fills::FillMode(fillMode);
    obj.m_fillType = FillType(fillType);
    obj.m_gradient = gradient;

    return in;
}
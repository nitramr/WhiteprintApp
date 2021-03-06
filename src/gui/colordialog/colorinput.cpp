/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2020 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "colorinput.h"
#include "ui_colorinput.h"
#include <QDebug>

#include <utilities.h>

ColorInput::ColorInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorInput)
{
    ui->setupUi(this);
    connectSlots();
}

ColorInput::~ColorInput()
{
    delete ui;
}

void ColorInput::connectSlots()
{
    connect(ui->sbRed, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbGreen, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbBlue, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->sbAlpha, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    connect(ui->txtHex, &color_widgets::ColorLineEdit::returnPressed, this, &ColorInput::updateColor);
}

void ColorInput::disconnectSlots()
{
    disconnect(ui->sbRed, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbGreen, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbBlue, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->sbAlpha, QOverload<int>::of(&QSpinBox::valueChanged), this, &ColorInput::updateColor);
    disconnect(ui->txtHex, &color_widgets::ColorLineEdit::returnPressed, this, &ColorInput::updateColor);
}

void ColorInput::setColor(const Color color)
{
    disconnectSlots();

    m_color = color;
    ui->txtHex->setColor(m_color);
    ui->sbRed->setValue( color.red() );
    ui->sbGreen->setValue( color.green() );
    ui->sbBlue->setValue( color.blue() );
    ui->sbAlpha->setValue( qRound(m_color.alphaF() * 100) );

    connectSlots();
}


/*!
 * \brief Update color that changed by input
 */
void ColorInput::updateColor()
{
    color_widgets::ColorLineEdit *hexEdit = dynamic_cast<color_widgets::ColorLineEdit*>(sender());

    if(hexEdit){
        m_color = ui->txtHex->color();
        m_color.setAlphaF( ui->sbAlpha->value() / 100.0 );
    }else{
        m_color.setRgb(ui->sbRed->value(), ui->sbGreen->value(), ui->sbBlue->value() );
        m_color.setAlphaF( ui->sbAlpha->value() / 100.0 );
    }

    setColor( m_color);

    emit colorChanged( m_color);
}

//void ColorInput::updateAlpha()
//{
//   // setColor( m_color, ui->sbAlpha->value());

//    emit alphaChanged( m_alpha);
//}

/**
 *  OSM
 *  Copyright (C) 2018  Pavel Smokotnin

 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef AXIS_H
#define AXIS_H
#include <optional>
#include "painteditem.h"
#include "palette.h"

namespace Fftchart {

    enum AxisType {linear, logarithmic};
    enum AxisDirection {vertical, horizontal};

class Axis : public PaintedItem
{
    Q_OBJECT
    static std::vector<float> ISO_LABELS;

private:
    AxisType _type = linear;
    AxisDirection _direction;
    const Palette &m_palette;
    std::vector<float> _labels;
    float _min, _max, _scale;
    float _lowLimit, _highLimit; //stop values
    float m_offset, m_centralLabel;
    std::optional<float> m_period;

public:
    Axis(AxisDirection d, const Palette &palette, QQuickItem *parent = Q_NULLPTR);
    void paint(QPainter *painter) noexcept;
    float convert(float value, float size) const;
    float reverse(float value, float size) const noexcept;
    float coordToValue(float coord) const noexcept;
    qreal coordToValue(qreal coord) const noexcept;

    void configure(AxisType type, float min, float max, unsigned int ticks = 0, float scale = 1.0f);

    float lowLimit() const {return _lowLimit;}
    float highLimit() const {return _highLimit;}

    void setMin(float v);
    float min() const {return _min;}

    void setScale(float v) {_scale = v;needUpdate();}
    float scale() const {return _scale;}

    void setMax(float v);
    float max() const {return _max;}

    void setISOLabels() {_labels = ISO_LABELS;}
    void autoLabels(unsigned int ticks);
    void setLabels(std::vector<float> labels) noexcept {_labels = labels;needUpdate();}

    void setType(AxisType t) {_type = t;needUpdate();}
    AxisType type() const {return _type;}

    float offset() const {return m_offset;}
    void setOffset(float offset);

    float centralLabel() const {return m_centralLabel;}
    void setCentralLabel(float central);

    void setPeriodic(float p);

public slots:
    void needUpdate();
    void parentWidthChanged();
    void parentHeightChanged();
};
}
#endif // AXIS_H

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
#include <algorithm>
#include "source.h"

using namespace Fftchart;
Source::Source(QObject *parent) : QObject(parent),
    _ftdata(nullptr),
    _impulseData(nullptr),
    _dataLength(1),
    m_deconvolutionSize(1),
    _fftSize(1),
    _active(false)
{

}
void Source::setActive(bool active)
{
    if (_active != active) {
        _active = active;
        emit activeChanged();
    }
}
void Source::setName(QString name)
{
    if (_name != name) {
        _name = name;
        emit nameChanged(_name);
    }
}
void Source::setColor(QColor color)
{
    if (_color != color) {
        _color = color;
        emit colorChanged(_color);
    }
}
void Source::setGlobalColor(int globalValue)
{
    if (globalValue < 19) {
        _color = Qt::GlobalColor(globalValue);
        emit colorChanged(_color);
    }
}
const float &Source::frequency(unsigned int i) const noexcept
{
    if (i >= _dataLength)
        return c_zero;
    return _ftdata[i].frequency;
}
const float &Source::module(unsigned int i) const noexcept
{
    if (i >= _dataLength)
        return c_zero;
    return _ftdata[i].module;
}
float Source::magnitude(unsigned int i) const noexcept
{
    if (i >= _dataLength)
        return c_zero;
    return 20.f * log10f(_ftdata[i].magnitude);
}
const float &Source::magnitudeRaw(unsigned int i) const noexcept
{
    if (i >= _dataLength)
        return c_zero;
    return _ftdata[i].magnitude;
}
const complex &Source::phase(unsigned int i) const noexcept
{
    if (i <= _dataLength)
        return _ftdata[i].phase;

    return _ftdata[0].phase;
}
const float &Source::coherence(unsigned int i) const noexcept
{
    if (i >= _dataLength)
        return c_zero;

    return _ftdata[i].coherence;
}
const float &Source::impulseTime(unsigned int i) const noexcept
{
    if (i >= m_deconvolutionSize)
        return c_zero;
    return _impulseData[i].time;
}
const float &Source::impulseValue(unsigned int i) const noexcept
{
    if (i >= m_deconvolutionSize)
        return c_zero;
    return _impulseData[i].value.real;
}
void Source::copy(FTData *dataDist, TimeData *timeDist)
{
    std::copy_n(_ftdata, size(), dataDist);
    std::copy_n(_impulseData, impulseSize(), timeDist);
}

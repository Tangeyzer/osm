/**
 *  OSM
 *  Copyright (C) 2019  Pavel Smokotnin

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
#ifndef MAGNITUDESERIESRENDERER_H
#define MAGNITUDESERIESRENDERER_H


#include "frequencybasedseriesrenderer.h"
namespace Fftchart {

class MagnitudeSeriesRenderer : public FrequencyBasedSeriesRenderer
{
public:
    MagnitudeSeriesRenderer();
    void renderSeries() override;
    void synchronize(QQuickFramebufferObject *item) override;

private:
    int m_posAttr, m_splineA,
        m_frequency1, m_frequency2,
        m_coherenceSpline,
        m_coherenceThresholdU, m_coherenceAlpha;
    unsigned int m_pointsPerOctave;
    float m_coherenceThreshold;
    bool m_coherence;
};
}
#endif // MAGNITUDESERIESRENDERER_H

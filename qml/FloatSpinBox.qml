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
import QtQuick 2.0
import QtQuick.Controls 2.2
Item {
    id: floatspinbox
    property real min : 0.0
    property real max : 1.0
    property alias from: floatspinbox.min
    property alias to: floatspinbox.max
    property real value : 0.0
    property int decimals: 2
    property real step : 0.1
    property real scale : 1.0
    property string tooltiptext
    property bool editable: true
    property int implicitWidth: 120
    width: spinbox.width
    height: spinbox.height

    SpinBox {
        id: spinbox
        property bool completed: false
        implicitWidth: floatspinbox.implicitWidth
        anchors.fill: parent

        /*
        value changes before a component is completed while applying limits (from and to)
        so we have to stop this event until the component is ccompleted
        */
        Component.onCompleted: function() {
            completed = true;
            value = Math.round(floatspinbox.value * floatspinbox.scale * Math.pow(10, floatspinbox.decimals));
        }
        onValueChanged: function() {
            if (completed) {
                floatspinbox.value = value / (floatspinbox.scale * Math.pow(10, floatspinbox.decimals))
            }
        }
        from:       Math.round(floatspinbox.min * floatspinbox.scale * Math.pow(10, floatspinbox.decimals))
        to:         Math.round(floatspinbox.max * floatspinbox.scale * Math.pow(10, floatspinbox.decimals))
        stepSize:   Math.round(floatspinbox.step * Math.pow(10, floatspinbox.decimals))
        editable:   floatspinbox.editable
        ToolTip.visible: hovered
        ToolTip.text: floatspinbox.tooltiptext

        validator: DoubleValidator {
            bottom: Math.min(spinbox.from, spinbox.to)
            top:  Math.max(spinbox.from, spinbox.to)
        }

        textFromValue: function(value, locale) {
            return Number(value / Math.pow(10, floatspinbox.decimals)).toLocaleString(locale, 'f', floatspinbox.decimals)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * Math.pow(10, floatspinbox.decimals)
        }
    }
}

import QtQuick 2.3
import QtQuick.Controls 1.2

import QGroundControl.FactSystem 1.0
import QGroundControl.FactControls 1.0
import QGroundControl.Controls 1.0
import QGroundControl.Palette 1.0

FactPanel {
    id:             panel
    anchors.fill:   parent
    color:          qgcPal.windowShadeDark

    QGCPalette { id: qgcPal; colorGroupEnabled: enabled }
    FactPanelController { id: controller; factPanel: panel }

    property Fact mapRollFact:      controller.getParameterFact(-1, "RC_MAP_ROLL")
    property Fact mapPitchFact:     controller.getParameterFact(-1, "RC_MAP_PITCH")
    property Fact mapYawFact:       controller.getParameterFact(-1, "RC_MAP_YAW")
    property Fact mapThrottleFact:  controller.getParameterFact(-1, "RC_MAP_THROTTLE")
    property Fact mapFlapsFact:     controller.getParameterFact(-1, "RC_MAP_FLAPS")
    property Fact mapAux1Fact:      controller.getParameterFact(-1, "RC_MAP_AUX1")
    property Fact mapAux2Fact:      controller.getParameterFact(-1, "RC_MAP_AUX2")

    Column {
        anchors.fill:       parent

        VehicleSummaryRow {
            labelText: qsTr("Work speed:")
            valueText: mapRollFact ? (mapRollFact.value === 0 ? qsTr("Setup required") : mapRollFact.valueString) : ""
        }

        VehicleSummaryRow {
            labelText: qsTr("Spray width:")
            valueText: mapPitchFact ? (mapPitchFact.value === 0 ? qsTr("Setup required") : mapPitchFact.valueString) : ""
        }

        VehicleSummaryRow {
            labelText: qsTr("Pump power:")
            valueText: mapYawFact ? (mapYawFact.value === 0 ? qsTr("Setup required") : mapYawFact.valueString) : ""
        }
    }
}

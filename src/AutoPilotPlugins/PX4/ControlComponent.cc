/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


#include "ControlComponent.h"
#include "PX4AutoPilotPlugin.h"

ControlComponent::ControlComponent(Vehicle* vehicle, AutoPilotPlugin* autopilot, QObject* parent) :
    VehicleComponent(vehicle, autopilot, parent),
    _name(tr("Control"))
{
}

QString ControlComponent::name(void) const
{
    return _name;
}

QString ControlComponent::description(void) const
{
    return tr("Control Setup");// is used to calibrate your transmitter. "
//              "It also assign channels for Roll, Pitch, Yaw and Throttle vehicle control as well as determining whether they are reversed.");
}

QString ControlComponent::iconResource(void) const
{
    return "/qmlimages/control.png";
}

bool ControlComponent::requiresSetup(void) const
{
    return _vehicle->parameterManager()->getParameter(-1, "COM_RC_IN_MODE")->rawValue().toInt() == 1 ? false : true;
}

bool ControlComponent::setupComplete(void) const
{
    if (_vehicle->parameterManager()->getParameter(-1, "COM_RC_IN_MODE")->rawValue().toInt() != 1) {
        // The best we can do to detect the need for a radio calibration is look for attitude
        // controls to be mapped.
        QStringList attitudeMappings;
        attitudeMappings << "RC_MAP_ROLL" << "RC_MAP_PITCH" << "RC_MAP_YAW" << "RC_MAP_THROTTLE";
        foreach(const QString &mapParam, attitudeMappings) {
            if (_vehicle->parameterManager()->getParameter(FactSystem::defaultComponentId, mapParam)->rawValue().toInt() == 0) {
                return false;
            }
        }
    }
    
    return true;
}

QStringList ControlComponent::setupCompleteChangedTriggerList(void) const
{
    QStringList triggers;
    
    triggers << "COM_RC_IN_MODE" << "RC_MAP_ROLL" << "RC_MAP_PITCH" << "RC_MAP_YAW" << "RC_MAP_THROTTLE";
    
    return triggers;
}

QUrl ControlComponent::setupSource(void) const
{
     return QUrl::fromUserInput("qrc:/qml/ControlComponent.qml");
    //return QUrl::fromLocalFile("C:/work/qgroundcontrol/src/AutoPilotPlugins/Common/ControlComponent.qml");
}

QUrl ControlComponent::summaryQmlSource(void) const
{
    return QUrl::fromUserInput("qrc:/qml/ControlComponentSummary.qml");
    //return QUrl::fromLocalFile("C:/work/qgroundcontrol/src/AutoPilotPlugins/PX4/ControlComponentSummary.qml");
}

﻿Imports ASCOM

Namespace My
    ' Do not modify this file. Do not delete this empty class definition.
    ' 
    ' The purpose of this code is to attach the two attributes [SettingsProvider] and [DeviceId]
    ' to the driver's MySettings class. The MySettings class is automatically generated by
    ' Visual Studio, so the attributes can't be added directly to the generated class.
    ' 
    ' Once these attributes are present on the MySettings class, then Visual Studio's settings designer
    ' can be used to manage driver settings and to bind settings directly to controls on
    ' the Setup Dialog. Instead of being stored in the usual place, the
    ' [SettingsProvider] attribute forces Visual Studio to use a custom settings provider
    ' that is installed with the ASCOM Platform. The custom settings provider uses
    ' ASCOM.Utilities.Profile as its underlying storage engine. The [DeviceId] attribute is
    ' used by the SettingsProvider to configure ASCOM.Utilities.Profile to store settings against
    ' the correct device profile.
    <DeviceIdAttribute("ASCOM.JoloFocuser.Focuser")> _
    <SettingsProvider(GetType(SettingsProvider))> _
    Partial Friend NotInheritable Class MySettings
    End Class
End Namespace
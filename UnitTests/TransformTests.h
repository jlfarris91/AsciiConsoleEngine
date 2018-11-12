#pragma once

DefineTestClass(TransformTests)
{
    DefineTestClass(LocalComponents)
    {
        DeclareTest(SettingLocalPositionShouldUpdateWorldPosition_NoParent);
        DeclareTest(SettingLocalRotationShouldUpdateWorldRotation_NoParent);
        DeclareTest(SettingLocalScaleShouldUpdateWorldScale_NoParent);
    };
    DefineTestClass(WorldComponents)
    {

    };
};
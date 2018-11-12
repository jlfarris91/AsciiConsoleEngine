#include "Keys.h"

DefineEnum3(KeyState, Up, Down, Triggered);

void Keys::InitializeMeta(Meta::TypeBuilder &builder)
{
    builder.AddReadOnlyField("Count", &Count);
    builder.AddReadOnlyField("Names", &Names);
    builder.AddReadOnlyField("Values", &Values);
}

const char *Keys::Names[0xFF] = {
    "None",
    "Backspace",
    "Tab",
    "Clear",
    "Enter",
    "Shift",
    "Control",
    "Alt",
    "Pause",
    "CapsLock",
    "Escape",
    "Space",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "Select",
    "Print",
    "Execute",
    "PrintScreen",
    "Insert",
    "Delete",
    "Help",
    "Zero",
    "One",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LeftWindowsKey",
    "RightWindowsKey",
    "ApplicationsKey",
    "Sleep",
    "NumPad0",
    "NumPad1",
    "NumPad2",
    "NumPad3",
    "NumPad4",
    "NumPad5",
    "NumPad6",
    "NumPad7",
    "NumPad8",
    "NumPad9",
    "Multiply",
    "Add",
    "Seperator",
    "Subtract",
    "Decimal",
    "Divide",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "Numlock",
    "ScrollLock",
    "LeftShift",
    "RightShift",
    "LeftControl",
    "RightContol",
    "LeftMenu",
    "RightMenu",
    "BrowserBack",
    "BrowserForward",
    "BrowserRefresh",
    "BrowserStop",
    "BrowserSearch",
    "BrowserFavorites",
    "BrowserHome",
    "VolumeMute",
    "VolumeDown",
    "VolumeUp",
    "NextTrack",
    "PreviousTrack",
    "StopMedia",
    "PlayPause",
    "LaunchMail",
    "SelectMedia",
    "LaunchApp1",
    "LaunchApp2",
    "OEM1",
    "OEMPlus",
    "OEMComma",
    "OEMMinus",
    "OEMPeriod",
    "OEM2",
    "OEM3",
    "OEM4",
    "OEM5",
    "OEM6",
    "OEM7",
    "OEM8",
    "OEM102",
    "Process",
    "Packet",
    "Attn",
    "CrSel",
    "ExSel",
    "EraseEOF",
    "Play",
    "Zoom",
    "PA1",
    "OEMClear"
};
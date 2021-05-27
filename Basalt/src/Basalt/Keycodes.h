#pragma once
#include "BEpch.h"

namespace Basalt
{
	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			// From glfw3.h
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47, /* / */

			Alpha0 = 48, /* 0 */
			Alpha1 = 49, /* 1 */
			Alpha2 = 50, /* 2 */
			Alpha3 = 51, /* 3 */
			Alpha4 = 52, /* 4 */
			Alpha5 = 53, /* 5 */
			Alpha6 = 54, /* 6 */
			Alpha7 = 55, /* 7 */
			Alpha8 = 56, /* 8 */
			Alpha9 = 57, /* 9 */

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */
			Tilde = 96,  /* ~ */

			World1 = 161, /* non-US #1 */
			World2 = 162, /* non-US #2 */

			/* Function keys */
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			RightArrow = 262,
			LeftArrow = 263,
			DownArrow = 264,
			UpArrow = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */
			KeyPad0 = 320,
			KeyPad1 = 321,
			KeyPad2 = 322,
			KeyPad3 = 323,
			KeyPad4 = 324,
			KeyPad5 = 325,
			KeyPad6 = 326,
			KeyPad7 = 327,
			KeyPad8 = 328,
			KeyPad9 = 329,
			KeyPadDecimal = 330,
			KeyPadDivide = 331,
			KeyPadMultiply = 332,
			KeyPadSubtract = 333,
			KeyPadAdd = 334,
			KeyPadEnter = 335,
			KeyPadEqual = 336,

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			LeftWindows = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			RightWindows = 347,
			Menu = 348
		};

		const std::unordered_map<unsigned char, KeyCode> ConvertToBasaltKeyCode
		{
			{VK_SPACE, Space},
			{VK_OEM_7, Apostrophe},
			{VK_OEM_COMMA, Comma},
			{VK_OEM_MINUS, Minus},
			{VK_OEM_PERIOD, Period},
			{VK_OEM_2, Slash},
			
			{'0', Alpha0},
			{'1', Alpha1},
			{'2', Alpha2},
			{'3', Alpha3},
			{'4', Alpha4},
			{'5', Alpha5},
			{'6', Alpha6},
			{'7', Alpha7},
			{'8', Alpha8},
			{'9', Alpha9},
			
			{VK_OEM_1, Semicolon},
			{VK_OEM_PLUS, Equal},
			
			{'A', A},
			{'B', B},
			{'C', C},
			{'D', D},
			{'E', E},
			{'F', F},
			{'G', G},
			{'H', H},
			{'I', I},
			{'J', J},
			{'K', K},
			{'L', L},
			{'M', M},
			{'N', N},
			{'O', O},
			{'P', P},
			{'Q', Q},
			{'R', R},
			{'S', S},
			{'T', T},
			{'U', U},
			{'V', V},
			{'W', W},
			{'X', X},
			{'Y', Y},
			{'Z', Z},

			{VK_OEM_4, LeftBracket},
			{VK_OEM_5, Backslash},
			{VK_OEM_6, RightBracket},
			{VK_OEM_3, GraveAccent},

			{VK_ESCAPE, Escape},
			{VK_RETURN, Enter},
			{VK_TAB, Tab},
			{VK_BACK, Backspace},
			{VK_INSERT, Insert},
			{VK_DELETE, Delete},
			{VK_RIGHT, RightArrow},
			{VK_LEFT, LeftArrow},
			{VK_DOWN, DownArrow},
			{VK_UP, UpArrow},
			{VK_PRIOR, PageUp},
			{VK_NEXT, PageDown},
			{VK_HOME, Home},
			{VK_END, End},
			{VK_CAPITAL, CapsLock},
			{VK_SCROLL, ScrollLock},
			{VK_NUMLOCK, NumLock},
			{VK_SNAPSHOT, PrintScreen},
			{VK_PAUSE, Pause},
			{VK_F1, F1},
			{VK_F2, F2},
			{VK_F3, F3},
			{VK_F4, F4},
			{VK_F5, F5},
			{VK_F6, F6},
			{VK_F7, F7},
			{VK_F8, F8},
			{VK_F9, F9},
			{VK_F10, F10},
			{VK_F11, F11},
			{VK_F12, F12},
			{VK_F13, F13},
			{VK_F14, F14},
			{VK_F15, F15},
			{VK_F16, F16},
			{VK_F17, F17},
			{VK_F18, F18},
			{VK_F19, F19},
			{VK_F20, F20},
			{VK_F21, F21},
			{VK_F22, F22},
			{VK_F23, F23},
			{VK_F24, F24},

			{VK_NUMPAD0, KeyPad0},
			{VK_NUMPAD1, KeyPad1},
			{VK_NUMPAD2, KeyPad2},
			{VK_NUMPAD3, KeyPad3},
			{VK_NUMPAD4, KeyPad4},
			{VK_NUMPAD5, KeyPad5},
			{VK_NUMPAD6, KeyPad6},
			{VK_NUMPAD7, KeyPad7},
			{VK_NUMPAD8, KeyPad8},
			{VK_NUMPAD9, KeyPad9},
			{VK_DECIMAL, KeyPadDecimal},
			{VK_DIVIDE, KeyPadDivide},
			{VK_MULTIPLY, KeyPadMultiply},
			{VK_SUBTRACT, KeyPadSubtract},
			{VK_ADD, KeyPadAdd},
			{0x255, KeyPadEnter},
			{VK_LSHIFT, LeftShift},
			{VK_LCONTROL, LeftControl},
			{VK_LMENU, LeftAlt},
			{VK_LWIN, LeftWindows},
			{VK_RSHIFT, RightShift },
			{VK_RCONTROL, RightControl },
			{VK_RMENU, RightAlt},
			{VK_RWIN, RightWindows},
		};
	}
	
}
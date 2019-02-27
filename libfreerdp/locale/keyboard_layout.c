/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Keyboard Layouts
 *
 * Copyright 2009-2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gi18n.h>

#include <winpr/crt.h>

#include "liblocale.h"

#include <freerdp/types.h>
#include <freerdp/scancode.h>
#include <freerdp/locale/keyboard.h>

/*
 * In Windows XP, this information is available in the system registry at
 * HKEY_LOCAL_MACHINE/SYSTEM/CurrentControlSet001/Control/Keyboard Layouts/
 */

static const RDP_KEYBOARD_LAYOUT RDP_KEYBOARD_LAYOUT_TABLE[] =
{
	{ KBD_ARABIC_101,		N_("Arabic (101)") },
	{ KBD_BULGARIAN,		N_("Bulgarian") },
	{ KBD_CHINESE_TRADITIONAL_US,	N_("Chinese (Traditional) - US Keyboard") },
	{ KBD_CZECH,			N_("Czech") },
	{ KBD_DANISH,			N_("Danish") },
	{ KBD_GERMAN,			N_("German") },
	{ KBD_GREEK,			N_("Greek") },
	{ KBD_US,			N_("US") },
	{ KBD_SPANISH,			N_("Spanish") },
	{ KBD_FINNISH,			N_("Finnish") },
	{ KBD_FRENCH,			N_("French") },
	{ KBD_HEBREW,			N_("Hebrew") },
	{ KBD_HUNGARIAN,		N_("Hungarian") },
	{ KBD_ICELANDIC,		N_("Icelandic") },
	{ KBD_ITALIAN,			N_("Italian") },
	{ KBD_JAPANESE,			N_("Japanese") },
	{ KBD_KOREAN,			N_("Korean") },
	{ KBD_DUTCH,			N_("Dutch") },
	{ KBD_NORWEGIAN,		N_("Norwegian") },
	{ KBD_POLISH_PROGRAMMERS,	N_("Polish (Programmers)") },
	{ KBD_PORTUGUESE_BRAZILIAN_ABNT, N_("Portuguese (Brazilian ABNT)") },
	{ KBD_ROMANIAN,			N_("Romanian") },
	{ KBD_RUSSIAN,			N_("Russian") },
	{ KBD_CROATIAN,			N_("Croatian") },
	{ KBD_SLOVAK,			N_("Slovak") },
	{ KBD_ALBANIAN,			N_("Albanian") },
	{ KBD_SWEDISH,			N_("Swedish") },
	{ KBD_THAI_KEDMANEE,		N_("Thai Kedmanee") },
	{ KBD_TURKISH_Q,		N_("Turkish Q") },
	{ KBD_URDU,			N_("Urdu") },
	{ KBD_UKRAINIAN,		N_("Ukrainian") },
	{ KBD_BELARUSIAN,		N_("Belarusian") },
	{ KBD_SLOVENIAN,		N_("Slovenian") },
	{ KBD_ESTONIAN,			N_("Estonian") },
	{ KBD_LATVIAN,			N_("Latvian") },
	{ KBD_LITHUANIAN_IBM,		N_("Lithuanian IBM") },
	{ KBD_FARSI,			N_("Farsi") },
	{ KBD_VIETNAMESE,		N_("Vietnamese") },
	{ KBD_ARMENIAN_EASTERN,		N_("Armenian Eastern") },
	{ KBD_AZERI_LATIN,		N_("Azeri Latin") },
	{ KBD_FYRO_MACEDONIAN,		N_("FYRO Macedonian") },
	{ KBD_GEORGIAN,			N_("Georgian") },
	{ KBD_FAEROESE,			N_("Faeroese") },
	{ KBD_DEVANAGARI_INSCRIPT,	N_("Devanagari - INSCRIPT") },
	{ KBD_MALTESE_47_KEY,		N_("Maltese 47-key") },
	{ KBD_NORWEGIAN_WITH_SAMI,	N_("Norwegian with Sami") },
	{ KBD_KAZAKH,			N_("Kazakh") },
	{ KBD_KYRGYZ_CYRILLIC,		N_("Kyrgyz Cyrillic") },
	{ KBD_TATAR,			N_("Tatar") },
	{ KBD_BENGALI,			N_("Bengali") },
	{ KBD_PUNJABI,			N_("Punjabi") },
	{ KBD_GUJARATI,			N_("Gujarati") },
	{ KBD_TAMIL,			N_("Tamil") },
	{ KBD_TELUGU,			N_("Telugu") },
	{ KBD_KANNADA,			N_("Kannada") },
	{ KBD_MALAYALAM,		N_("Malayalam") },
	{ KBD_MARATHI,			N_("Marathi") },
	{ KBD_MONGOLIAN_CYRILLIC,	N_("Mongolian Cyrillic") },
	{ KBD_UNITED_KINGDOM_EXTENDED,	N_("United Kingdom Extended") },
	{ KBD_SYRIAC,			N_("Syriac") },
	{ KBD_NEPALI,			N_("Nepali") },
	{ KBD_PASHTO,			N_("Pashto") },
	{ KBD_DIVEHI_PHONETIC,		N_("Divehi Phonetic") },
	{ KBD_LUXEMBOURGISH,		N_("Luxembourgish") },
	{ KBD_MAORI,			N_("Maori") },
	{ KBD_CHINESE_SIMPLIFIED_US,	N_("Chinese (Simplified) - US Keyboard") },
	{ KBD_SWISS_GERMAN,		N_("Swiss German") },
	{ KBD_UNITED_KINGDOM,		N_("United Kingdom") },
	{ KBD_LATIN_AMERICAN,		N_("Latin American") },
	{ KBD_BELGIAN_FRENCH,		N_("Belgian French") },
	{ KBD_BELGIAN_PERIOD,		N_("Belgian (Period)") },
	{ KBD_PORTUGUESE,		N_("Portuguese") },
	{ KBD_SERBIAN_LATIN,		N_("Serbian (Latin)") },
	{ KBD_AZERI_CYRILLIC,		N_("Azeri Cyrillic") },
	{ KBD_SWEDISH_WITH_SAMI,	N_("Swedish with Sami") },
	{ KBD_UZBEK_CYRILLIC,		N_("Uzbek Cyrillic") },
	{ KBD_INUKTITUT_LATIN,		N_("Inuktitut Latin") },
	{ KBD_CANADIAN_FRENCH_LEGACY,	N_("Canadian French (legacy)") },
	{ KBD_SERBIAN_CYRILLIC,		N_("Serbian (Cyrillic)") },
	{ KBD_CANADIAN_FRENCH,		N_("Canadian French") },
	{ KBD_CANADIAN_ENGLISH,		N_("Canadian English") },
	{ KBD_SWISS_FRENCH,		N_("Swiss French") },
	{ KBD_BOSNIAN,			N_("Bosnian") },
	{ KBD_IRISH,			N_("Irish") },
	{ KBD_BOSNIAN_CYRILLIC,		N_("Bosnian Cyrillic") }
};

struct _RDP_KEYBOARD_LAYOUT_VARIANT
{
	DWORD code; /* Keyboard layout code */
	DWORD id; /* Keyboard variant ID */
	const char* name; /* Keyboard layout variant name */
};
typedef struct _RDP_KEYBOARD_LAYOUT_VARIANT RDP_KEYBOARD_LAYOUT_VARIANT;

static const RDP_KEYBOARD_LAYOUT_VARIANT RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[] =
{
	{ KBD_ARABIC_102,				0x0028, N_("Arabic (102)") },
	{ KBD_BULGARIAN_LATIN,				0x0004, N_("Bulgarian (Latin)") },
	{ KBD_CZECH_QWERTY,				0x0005, N_("Czech (QWERTY)") },
	{ KBD_GERMAN_IBM,				0x0012, N_("German (IBM)") },
	{ KBD_GREEK_220,				0x0016, N_("Greek (220)") },
	{ KBD_UNITED_STATES_DVORAK,			0x0002, N_("United States-Dvorak") },
	{ KBD_SPANISH_VARIATION,			0x0086, N_("Spanish Variation") },
	{ KBD_HUNGARIAN_101_KEY,			0x0006, N_("Hungarian 101-key") },
	{ KBD_ITALIAN_142,				0x0003, N_("Italian (142)") },
	{ KBD_POLISH_214,				0x0007, N_("Polish (214)") },
	{ KBD_PORTUGUESE_BRAZILIAN_ABNT2,		0x001D, N_("Portuguese (Brazilian ABNT2)") },
	{ KBD_RUSSIAN_TYPEWRITER,			0x0008, N_("Russian (Typewriter)") },
	{ KBD_SLOVAK_QWERTY,				0x0013, N_("Slovak (QWERTY)") },
	{ KBD_THAI_PATTACHOTE,				0x0021, N_("Thai Pattachote") },
	{ KBD_TURKISH_F,				0x0014, N_("Turkish F") },
	{ KBD_LATVIAN_QWERTY,				0x0015, N_("Latvian (QWERTY)") },
	{ KBD_LITHUANIAN,				0x0027, N_("Lithuanian") },
	{ KBD_ARMENIAN_WESTERN,				0x0025, N_("Armenian Western") },
	{ KBD_HINDI_TRADITIONAL,			0x000C, N_("Hindi Traditional") },
	{ KBD_MALTESE_48_KEY,				0x002B, N_("Maltese 48-key") },
	{ KBD_SAMI_EXTENDED_NORWAY,			0x002C, N_("Sami Extended Norway") },
	{ KBD_BENGALI_INSCRIPT,				0x002A, N_("Bengali (Inscript)") },
	{ KBD_SYRIAC_PHONETIC,				0x000E, N_("Syriac Phonetic") },
	{ KBD_DIVEHI_TYPEWRITER,			0x000D, N_("Divehi Typewriter") },
	{ KBD_BELGIAN_COMMA,				0x001E, N_("Belgian (Comma)") },
	{ KBD_FINNISH_WITH_SAMI,			0x002D, N_("Finnish with Sami") },
	{ KBD_CANADIAN_MULTILINGUAL_STANDARD,		0x0020, N_("Canadian Multilingual Standard") },
	{ KBD_GAELIC,					0x0026, N_("Gaelic") },
	{ KBD_ARABIC_102_AZERTY,			0x0029, N_("Arabic (102) AZERTY") },
	{ KBD_CZECH_PROGRAMMERS,			0x000A, N_("Czech Programmers") },
	{ KBD_GREEK_319,				0x0018, N_("Greek (319)") },
	{ KBD_UNITED_STATES_INTERNATIONAL,		0x0001, N_("United States-International") },
	{ KBD_THAI_KEDMANEE_NON_SHIFTLOCK,		0x0022, N_("Thai Kedmanee (non-ShiftLock)") },
	{ KBD_SAMI_EXTENDED_FINLAND_SWEDEN,		0x002E, N_("Sami Extended Finland-Sweden") },
	{ KBD_GREEK_220_LATIN,				0x0017, N_("Greek (220) Latin") },
	{ KBD_UNITED_STATES_DVORAK_FOR_LEFT_HAND,	0x001A, N_("United States-Dvorak for left hand") },
	{ KBD_THAI_PATTACHOTE_NON_SHIFTLOCK,		0x0023, N_("Thai Pattachote (non-ShiftLock)") },
	{ KBD_GREEK_319_LATIN,				0x0011, N_("Greek (319) Latin") },
	{ KBD_UNITED_STATES_DVORAK_FOR_RIGHT_HAND,	0x001B, N_("United States-Dvorak for right hand") },
	{ KBD_UNITED_STATES_DVORAK_PROGRAMMER,		0x001C, N_("United States-Programmer Dvorak") },
	{ KBD_GREEK_LATIN,				0x0019, N_("Greek Latin") },
	{ KBD_US_ENGLISH_TABLE_FOR_IBM_ARABIC_238_L,	0x000B, N_("US English Table for IBM Arabic 238_L") },
	{ KBD_GREEK_POLYTONIC,				0x001F, N_("Greek Polytonic") },
	{ KBD_FRENCH_BEPO,				0x00C0, N_("French Bépo") },
	{ KBD_GERMAN_NEO,				0x00C0, N_("German Neo") }
};

/* Input Method Editor (IME) */

struct _RDP_KEYBOARD_IME
{
	DWORD code; /* Keyboard layout code */
	const char* file; /* IME file */
	const char* name; /* Keyboard layout name */
};
typedef struct _RDP_KEYBOARD_IME RDP_KEYBOARD_IME;

/* Global Input Method Editors (IME) */

static const RDP_KEYBOARD_IME RDP_KEYBOARD_IME_TABLE[] =
{
	{ KBD_CHINESE_TRADITIONAL_PHONETIC,			"phon.ime", N_("Chinese (Traditional) - Phonetic") },
	{ KBD_JAPANESE_INPUT_SYSTEM_MS_IME2002,			"imjp81.ime", N_("Japanese Input System (MS-IME2002)") },
	{ KBD_KOREAN_INPUT_SYSTEM_IME_2000,			"imekr61.ime", N_("Korean Input System (IME 2000)") },
	{ KBD_CHINESE_SIMPLIFIED_QUANPIN,			"winpy.ime", N_("Chinese (Simplified) - QuanPin") },
	{ KBD_CHINESE_TRADITIONAL_CHANGJIE,			"chajei.ime", N_("Chinese (Traditional) - ChangJie") },
	{ KBD_CHINESE_SIMPLIFIED_SHUANGPIN,			"winsp.ime", N_("Chinese (Simplified) - ShuangPin") },
	{ KBD_CHINESE_TRADITIONAL_QUICK,			"quick.ime", N_("Chinese (Traditional) - Quick") },
	{ KBD_CHINESE_SIMPLIFIED_ZHENGMA,			"winzm.ime", N_("Chinese (Simplified) - ZhengMa") },
	{ KBD_CHINESE_TRADITIONAL_BIG5_CODE,			"winime.ime", N_("Chinese (Traditional) - Big5 Code") },
	{ KBD_CHINESE_TRADITIONAL_ARRAY,			"winar30.ime", N_("Chinese (Traditional) - Array") },
	{ KBD_CHINESE_SIMPLIFIED_NEIMA,				"wingb.ime", N_("Chinese (Simplified) - NeiMa") },
	{ KBD_CHINESE_TRADITIONAL_DAYI,				"dayi.ime", N_("Chinese (Traditional) - DaYi") },
	{ KBD_CHINESE_TRADITIONAL_UNICODE,			"unicdime.ime", N_("Chinese (Traditional) - Unicode") },
	{ KBD_CHINESE_TRADITIONAL_NEW_PHONETIC,			"TINTLGNT.IME", N_("Chinese (Traditional) - New Phonetic") },
	{ KBD_CHINESE_TRADITIONAL_NEW_CHANGJIE,			"CINTLGNT.IME", N_("Chinese (Traditional) - New ChangJie") },
	{ KBD_CHINESE_TRADITIONAL_MICROSOFT_PINYIN_IME_3,	"pintlgnt.ime", N_("Chinese (Traditional) - Microsoft Pinyin IME 3.0") },
	{ KBD_CHINESE_TRADITIONAL_ALPHANUMERIC,			"romanime.ime", N_("Chinese (Traditional) - Alphanumeric") }
};

void freerdp_keyboard_layouts_free(RDP_KEYBOARD_LAYOUT* layouts)
{
	RDP_KEYBOARD_LAYOUT* current = layouts;

	if (!layouts)
		return;

	while ((current->code != 0) && (current->name != NULL))
	{
		free(current->name);
		current ++;
	}

	free(layouts);
}

RDP_KEYBOARD_LAYOUT* freerdp_keyboard_get_layouts(DWORD types)
{
	size_t num, length, i;
	RDP_KEYBOARD_LAYOUT* layouts;
	RDP_KEYBOARD_LAYOUT* new;
	num = 0;
	layouts = (RDP_KEYBOARD_LAYOUT*) calloc((num + 1), sizeof(RDP_KEYBOARD_LAYOUT));

	if (!layouts)
		return NULL;

	if ((types & RDP_KEYBOARD_LAYOUT_TYPE_STANDARD) != 0)
	{
		length = ARRAYSIZE(RDP_KEYBOARD_LAYOUT_TABLE);
		new = (RDP_KEYBOARD_LAYOUT*) realloc(layouts, (num + length + 1) * sizeof(RDP_KEYBOARD_LAYOUT));

		if (!new)
			goto fail;

		layouts = new;

		for (i = 0; i < length; i++, num++)
		{
			layouts[num].code = RDP_KEYBOARD_LAYOUT_TABLE[i].code;
			layouts[num].name = _strdup(RDP_KEYBOARD_LAYOUT_TABLE[i].name);

			if (!layouts[num].name)
				goto fail;
		}
	}

	if ((types & RDP_KEYBOARD_LAYOUT_TYPE_VARIANT) != 0)
	{
		length = ARRAYSIZE(RDP_KEYBOARD_LAYOUT_VARIANT_TABLE);
		new = (RDP_KEYBOARD_LAYOUT*) realloc(layouts, (num + length + 1) * sizeof(RDP_KEYBOARD_LAYOUT));

		if (!new)
			goto fail;

		layouts = new;

		for (i = 0; i < length; i++, num++)
		{
			layouts[num].code = RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].code;
			layouts[num].name = _strdup(RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].name);

			if (!layouts[num].name)
				goto fail;
		}
	}

	if ((types & RDP_KEYBOARD_LAYOUT_TYPE_IME) != 0)
	{
		length = ARRAYSIZE(RDP_KEYBOARD_IME_TABLE);
		new = (RDP_KEYBOARD_LAYOUT*) realloc(layouts, (num + length + 1) * sizeof(RDP_KEYBOARD_LAYOUT));

		if (!new)
			goto fail;

		layouts = new;

		for (i = 0; i < length; i++, num++)
		{
			layouts[num].code = RDP_KEYBOARD_IME_TABLE[i].code;
			layouts[num].name = _strdup(RDP_KEYBOARD_IME_TABLE[i].name);

			if (!layouts[num].name)
				goto fail;
		}
	}

	ZeroMemory(&layouts[num], sizeof(RDP_KEYBOARD_LAYOUT));
	return layouts;
fail:
	freerdp_keyboard_layouts_free(layouts);
	return NULL;
}

const char* freerdp_keyboard_get_layout_name_from_id(DWORD keyboardLayoutID)
{
	size_t i;

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_LAYOUT_TABLE); i++)
	{
		if (RDP_KEYBOARD_LAYOUT_TABLE[i].code == keyboardLayoutID)
			return RDP_KEYBOARD_LAYOUT_TABLE[i].name;
	}

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_LAYOUT_VARIANT_TABLE); i++)
	{
		if (RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].code == keyboardLayoutID)
			return RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].name;
	}

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_IME_TABLE); i++)
	{
		if (RDP_KEYBOARD_IME_TABLE[i].code == keyboardLayoutID)
			return RDP_KEYBOARD_IME_TABLE[i].name;
	}

	return "unknown";
}

DWORD freerdp_keyboard_get_layout_id_from_name(const char* name)
{
	size_t i;

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_LAYOUT_TABLE); i++)
	{
		if (strcmp(RDP_KEYBOARD_LAYOUT_TABLE[i].name, name) == 0)
			return RDP_KEYBOARD_LAYOUT_TABLE[i].code;
	}

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_LAYOUT_VARIANT_TABLE); i++)
	{
		if (strcmp(RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].name, name) == 0)
			return RDP_KEYBOARD_LAYOUT_VARIANT_TABLE[i].code;
	}

	for (i = 0; i < ARRAYSIZE(RDP_KEYBOARD_IME_TABLE); i++)
	{
		if (strcmp(RDP_KEYBOARD_IME_TABLE[i].name, name) == 0)
			return RDP_KEYBOARD_IME_TABLE[i].code;
	}

	return 0;
}

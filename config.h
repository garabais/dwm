/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 10;       /* gap pixel between windows */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 30;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Noto Sans:size=13", "monospace:size=10" };
static const char col_black[]       = "#2E3440";
static const char col_dark_gray[]   = "#4C566A";
static const char col_light_gray[]  = "#ECEFF4";
static const char col_white[]       = "#ECEFF4";
static const char col_blue[]        = "#81A1C1";
static const char col_dark_blue[]   = "#5E81AC";
static const char *colors[][3]      = {
	/*                 fg              bg         border   */
	[SchemeNorm]   = { col_white,      col_black, col_dark_gray },
	[SchemeSel]    = { col_white,      col_blue,  col_dark_blue  },
	[SchemeTitle]  = { col_light_gray, col_black, col_dark_gray  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Special keys short definition */
#include <X11/XF86keysym.h>
#define XK_BrightnessUp      XF86XK_MonBrightnessUp
#define XK_BrightnessDown    XF86XK_MonBrightnessDown
#define XK_AudioUp           XF86XK_AudioRaiseVolume
#define XK_AudioDown         XF86XK_AudioLowerVolume
#define XK_AudioMute         XF86XK_AudioMute
#define XK_AudioPlay         XF86XK_AudioPlay
#define XK_AudioNext         XF86XK_AudioNext
#define XK_AudioPrev         XF86XK_AudioPrev

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *launchercmd[]  = { "rofi", "-show", NULL };
static const char *gpulaunchercmd[]  = { "prime-run", "rofi", "-show", NULL };
static const char *powermenucmd[]  = { "powermenu", NULL };
static const char *browsercmd[]  = { "google-chrome-stable", NULL };
static const char *incognitobrowsercmd[]  = { "google-chrome-stable", "--incognito", NULL };
static const char *unicodeselectorcmd[]  = { "unipicker", "--command", "rofi -dmenu", "--copy",NULL };
static const char screenshotcmd[] = "maim -s -u | xclip -selection clipboard -t image/png -i";
static const char *brightnessupcmd[]  = { "backlight", "-i", "750", NULL };
static const char *brightnessdowncmd[]  = { "backlight", "-d", "750", NULL };
static const char *audioupcmd[]  = { "pulsemixer", "--change-volume", "+1", NULL };
static const char *audiodowncmd[]  = { "pulsemixer", "--change-volume", "-1", NULL };
static const char *audioupmulticmd[]  = { "pulsemixer", "--change-volume", "+10", NULL };
static const char *audiodownmulticmd[]  = { "pulsemixer", "--change-volume", "-10", NULL };
static const char *audiomutecmd[]  = { "pulsemixer", "--toggle-mute", NULL };
static const char *audioplaycmd[]  = { "playerctl", "play-pause", NULL };
static const char *audionextcmd[]  = { "playerctl", "next", NULL };
static const char *audioprevcmd[]  = { "playerctl", "previous", NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier                     key                 function                argument */
	{ MODKEY,                       XK_space,           spawn,                  {.v = launchercmd } },
	{ MODKEY|ShiftMask,             XK_space,           spawn,                  {.v = gpulaunchercmd } },
	{ MODKEY,                       XK_Return,          spawn,                  {.v = termcmd } },
	{ MODKEY,                       XK_Escape,          spawn,                  {.v = powermenucmd } },
	{ MODKEY,                       XK_n,               spawn,                  {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_n,               spawn,                  {.v = incognitobrowsercmd } },
	{ MODKEY,                       XK_grave,           spawn,                  {.v = unicodeselectorcmd } },
	{ MODKEY,                       XK_p,               spawn,                  SHCMD(screenshotcmd) },
	{ MODKEY,                       XK_b,               togglebar,              {0} },
	{ MODKEY,                       XK_j,               focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,               focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,               movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,               movestack,              {.i = -1 } },
	{ MODKEY,                       XK_i,               incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,               incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,               {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,          zoom,                   {0} },
	{ MODKEY,                       XK_backslash,       view,                   {0} },
	{ MODKEY,                       XK_Tab,             view,                   {0} },
	{ MODKEY,                       XK_w,               killclient,             {0} },
	{ MODKEY,                       XK_t,               setlayout,              {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_s,               setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,               setlayout,              {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Tab,             setlayout,              {0} },
	{ MODKEY,                       XK_s,               togglefloating,         {0} },
	{ MODKEY,                       XK_f,               togglefullscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_f,               togglefakefullscreen,   {0} },
	{ MODKEY,                       XK_0,               view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,           focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,          focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,           tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,          tagmon,                 {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketright,    tagswapmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,     tagswapmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_backslash,       tagswapmon,             {0} },
	{ MODKEY,                       XK_bracketleft,     shiftview,              {.i = -1 } },
	{ MODKEY,                       XK_bracketright,    shiftview,              {.i = +1 } },
	TAGKEYS(                        XK_1,                                       0)
	TAGKEYS(                        XK_2,                                       1)
	TAGKEYS(                        XK_3,                                       2)
	TAGKEYS(                        XK_4,                                       3)
	TAGKEYS(                        XK_5,                                       4)
	TAGKEYS(                        XK_6,                                       5)
	TAGKEYS(                        XK_7,                                       6)
	TAGKEYS(                        XK_8,                                       7)
	TAGKEYS(                        XK_9,                                       8)
	{ MODKEY|ShiftMask,             XK_q,               quit,                   {0} },
	{0,                             XK_BrightnessUp,    spawn,                  {.v = brightnessupcmd } },
	{0,                             XK_BrightnessDown,  spawn,                  {.v = brightnessdowncmd } },
	{0,                             XK_AudioUp,         spawn,                  {.v = audioupcmd } },
	{0,                             XK_AudioDown,       spawn,                  {.v = audiodowncmd } },
	{ShiftMask,                     XK_AudioUp,         spawn,                  {.v = audioupmulticmd } },
	{ShiftMask,                     XK_AudioDown,       spawn,                  {.v = audiodownmulticmd } },
	{0,                             XK_AudioMute,       spawn,                  {.v = audiomutecmd } },
	{0,                             XK_AudioPlay,       spawn,                  {.v = audioplaycmd } },
	{0,                             XK_AudioNext,       spawn,                  {.v = audionextcmd } },
	{0,                             XK_AudioPrev,       spawn,                  {.v = audioprevcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


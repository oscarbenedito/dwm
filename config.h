/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx        = 2;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const char *fonts[]          = {
	"monospace:size=10",
	"Font Awesome 5 Free Regular:size=10",
	"Font Awesome 5 Free Solid:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title    tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ "Firefox", NULL,     NULL,      1 << 1,          0,          0,          0,         1,       -1 },
	{ "Signal",  NULL,     NULL,      1 << 8,          0,          0,          0,         1,       -1 },
	{ "thunderbird",NULL,  NULL,      1 << 6,          0,          0,          0,         1,       -1 },
	{ "Alacritty",NULL,    NULL,           0,          0,          0,          1,        -1,       -1 },
	{ "Gcr-prompter",NULL, NULL,           0,          1,          1,          0,         1,       -1 }, /* GPG password prompt */
	{ NULL,      NULL,     "Event Tester", 0,          0,          1,          0,         1,       -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

/* #define FORCE_VSPLIT 1  /1* nrowgrid layout: force two clients to always split vertically *1/ */
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[]D",      deck },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ ":::",      gaplessgrid },
	{ "---",      horizgrid },
	/* { "HHH",      grid }, */
	/* { "###",      nrowgrid }, */
	/* { "|M|",      centeredmaster }, */
	/* { ">M>",      centeredfloatingmaster }, */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
	{ "normbgcolor",        STRING,  &normbgcolor },
	{ "normbordercolor",    STRING,  &normbordercolor },
	{ "normfgcolor",        STRING,  &normfgcolor },
	{ "selbgcolor",         STRING,  &selbgcolor },
	{ "selbordercolor",     STRING,  &selbordercolor },
	{ "selfgcolor",         STRING,  &selfgcolor },
	{ "borderpx",           INTEGER, &borderpx },
	{ "snap",               INTEGER, &snap },
	{ "showbar",            INTEGER, &showbar },
	{ "topbar",             INTEGER, &topbar },
	{ "nmaster",            INTEGER, &nmaster },
	{ "resizehints",        INTEGER, &resizehints },
	{ "mfact",              FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier             key        function        argument */
	/* dwm */
	{ MODKEY,               XK_p,           spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,               XK_KP_Enter,    spawn,          {.v = termcmd } }, /* Numeric pad return */
	{ MODKEY,               XK_b,           togglebar,      {0} },
	{ MODKEY,               XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,               XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,               XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_plus,        incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_equal,       incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_minus,       incnmaster,     {.i = -1 } },
	{ MODKEY,               XK_g,           incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_g,           incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_b,           togglegaps,     {0} },
	{ MODKEY,               XK_space,       zoom,           {0} },
	{ MODKEY,               XK_Tab,         view,           {0} }, /* previous tag */
	{ MODKEY,               XK_q,           killclient,     {0} },
	{ MODKEY|ShiftMask,     XK_space,       togglefloating, {0} },
	{ MODKEY,               XK_0,           view,           {.ui = ~0 } }, /* all tags active */
	{ MODKEY|ShiftMask,     XK_0,           tag,            {.ui = ~0 } }, /* current window to all tags */
	{ MODKEY,               XK_comma,       focusmon,       {.i = -1 } }, /* previous monitor */
	{ MODKEY,               XK_period,      focusmon,       {.i = +1 } }, /* next monitor */
	{ MODKEY|ShiftMask,     XK_comma,       tagmon,         {.i = -1 } }, /* send window to previous monitor */
	{ MODKEY|ShiftMask,     XK_period,      tagmon,         {.i = +1 } }, /* send window to next monitor */
	{ MODKEY,               XK_o,           spawn,          SHCMD("session-dmenu") },
	{ MODKEY|ControlMask,   XK_q,           quit,           {0} },

	/* layouts */
	{ MODKEY,               XK_t,           setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,     XK_t,           setlayout,      {.v = &layouts[1]} }, /* floating */
	{ MODKEY,               XK_i,           setlayout,      {.v = &layouts[2]} }, /* monocle */
	{ MODKEY,               XK_y,           setlayout,      {.v = &layouts[3]} }, /* bottomstack */
	{ MODKEY|ShiftMask,     XK_y,           setlayout,      {.v = &layouts[4]} }, /* bottomstack horizontal */
	{ MODKEY,               XK_u,           setlayout,      {.v = &layouts[5]} }, /* deck */
	{ MODKEY,               XK_r,           setlayout,      {.v = &layouts[6]} }, /* fibonacci */
	{ MODKEY|ShiftMask,     XK_r,           setlayout,      {.v = &layouts[7]} }, /* fibonacci var */
	{ MODKEY,               XK_w,           setlayout,      {.v = &layouts[8]} }, /* grid */
	{ MODKEY|ShiftMask,     XK_w,           setlayout,      {.v = &layouts[9]} }, /* horizontal grid */

	/* utilities */
	{ 0,        XF86XK_AudioRaiseVolume,    spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 5%+ && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY,   XK_plus,                    spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 5%+ && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY,   XK_equal,                   spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 5%+ && pkill -RTMIN+1 dwmblocks") },
	{ ShiftMask,XF86XK_AudioRaiseVolume,    spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 1%+ && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY|ShiftMask,XK_plus,             spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 1%+ && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY|ShiftMask,XK_equal,            spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 1%+ && pkill -RTMIN+1 dwmblocks") },
	{ 0,        XF86XK_AudioLowerVolume,    spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 5%- && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY,   XK_minus,                   spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 5%- && pkill -RTMIN+1 dwmblocks") },
	{ ShiftMask,XF86XK_AudioLowerVolume,    spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 1%- && pkill -RTMIN+1 dwmblocks") },
	{ MODKEY|ShiftMask,XK_minus,            spawn,  SHCMD("amixer -q -D pulse sset Master unmute && amixer -q -D pulse sset Master 1%- && pkill -RTMIN+1 dwmblocks") },
	{ 0,        XF86XK_AudioMute,           spawn,  SHCMD("amixer -q -D pulse sset Master toggle && pkill -RTMIN+1 dwmblocks") },
	{ 0,        XF86XK_MonBrightnessUp,     spawn,  SHCMD("xbacklight -inc 5 && pkill -RTMIN+2 dwmblocks") },
	{ 0,        XF86XK_MonBrightnessDown,   spawn,  SHCMD("xbacklight -dec 5 && pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask,XF86XK_MonBrightnessUp,     spawn,  SHCMD("xbacklight -inc 1 && pkill -RTMIN+2 dwmblocks") },
	{ ShiftMask,XF86XK_MonBrightnessDown,   spawn,  SHCMD("xbacklight -dec 1 && pkill -RTMIN+2 dwmblocks") },
	{ MODKEY,               XK_m,           spawn,  SHCMD("mount-drive") },
	{ 0,                    XK_Print,       spawn,  SHCMD("sleep 0.2 && scrot --select /tmp/screenshot-$(date +%F_%T).png --exec 'xclip -selection c -target image/png < $f'; notify-send 'Screenshot copied to clipboard'") },
	{ MODKEY,               XK_s,           spawn,  SHCMD("sleep 0.2 && scrot --select /tmp/screenshot-$(date +%F_%T).png --exec 'xclip -selection c -target image/png < $f'; notify-send 'Screenshot copied to clipboard'") },
	{ ShiftMask,            XK_Print,       spawn,  SHCMD("scrot /tmp/screenshot-$(date +%F_%T).png --exec 'xclip -selection c -target image/png < $f'; notify-send 'Screenshot copied to clipboard'") },
	{ MODKEY|ShiftMask,     XK_s,           spawn,  SHCMD("scrot /tmp/screenshot-$(date +%F_%T).png --exec 'xclip -selection c -target image/png < $f'; notify-send 'Screenshot copied to clipboard'") },
	{ MODKEY,               XK_n,           spawn,  SHCMD("mktemp | tr -d \\\\n | xclip") },
	{ MODKEY|ShiftMask,     XK_n,           spawn,  SHCMD("mktemp --directory | tr -d \\\\n | xclip") },
	{ ControlMask,          XK_Escape,      spawn,  SHCMD("dunstctl close") },
	{ ControlMask,          XK_grave,       spawn,  SHCMD("dunstctl history-pop") },

	/* applications */
	{ MODKEY,               XK_f,           spawn,  SHCMD("firefox") },
	{ MODKEY,               XK_x,           spawn,  SHCMD("signal-desktop --no-sandbox") },
	{ MODKEY,               XK_e,           spawn,  SHCMD("thunderbird") },
	{ MODKEY,               XK_c,           spawn,  SHCMD("passmenu --type-all") },
	{ MODKEY|ShiftMask,     XK_c,           spawn,  SHCMD("passmenu --type") },

	/* tags */
	TAGKEYS(                XK_1,           0)
	TAGKEYS(                XK_2,           1)
	TAGKEYS(                XK_3,           2)
	TAGKEYS(                XK_4,           3)
	TAGKEYS(                XK_5,           4)
	TAGKEYS(                XK_6,           5)
	TAGKEYS(                XK_7,           6)
	TAGKEYS(                XK_8,           7)
	TAGKEYS(                XK_9,           8)
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


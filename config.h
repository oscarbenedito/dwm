/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 0;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray        = 1;        /* 0 means no systray */
static const char *fonts[]          = {
	"monospace:size=10",
	"Font Awesome 5 Free Regular:size=10",
	"Font Awesome 5 Free Solid:size=10"
};
static const char dmenufont[]       = "monospace:size=10";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#eeeeee", "#000000", "#444444" },
	[SchemeSel]  = { "#eeeeee", "#285577", "#a8c138" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title    tags mask  iscentered  isfloating  isterminal  noswallow  monitor */
	{ "firefox",     NULL, NULL,      1 << 1,          0,          0,          0,         1,       -1 },
	{ "Signal",      NULL, NULL,      1 << 8,          0,          0,          0,         0,       -1 },
	{ "Thunderbird", NULL, NULL,      1 << 6,          0,          0,          0,         0,       -1 },
	{ "Alacritty",   NULL, NULL,           0,          0,          0,          1,        -1,       -1 },
	{ "Pavucontrol", NULL, NULL,           0,          1,          1,          0,         1,       -1 },
	{ "Gcr-prompter",NULL, NULL,           0,          1,          1,          0,         1,       -1 }, /* GPG password prompt */
	{ NULL,      NULL,     "Event Tester", 0,          0,          1,          0,         1,       -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]D",      deck },
	{ "TTT",      bstack },
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
	{ MODKEY|ShiftMask,     XK_i,           setlayout,      {.v = &layouts[3]} }, /* deck */
	{ MODKEY|ControlMask,   XK_t,           setlayout,      {.v = &layouts[4]} }, /* bottomstack */

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
	{ MODKEY,               XK_x,           spawn,  SHCMD("signal-desktop") },
	{ MODKEY,               XK_e,           spawn,  SHCMD("thunderbird") },
	{ MODKEY,               XK_c,           spawn,  SHCMD("altpassmenu --type-all") },
	{ MODKEY|ShiftMask,     XK_c,           spawn,  SHCMD("altpassmenu --type") },

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


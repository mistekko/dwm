/* See LICENSE file for copyright and license details. */

#define STATUSBAR "dwmblocks"

/* appearance */
/* #include "/home/mistekko/.cache/wal/colors-wal-dwm.h" */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 1;	/* 1 means swallow floating windows by default */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Andale Mono:size=14" };
static const char dmenufont[]       = "Andale Mono:size=14";
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
static const unsigned int baralpha = 204; // alpha_centigrade * 51 / 20;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance title   mask    float? term?  !swallow  mon. */
	{ "URxvt",     NULL,	NULL,   0,	0,     1 },
	{ "st-256color",  NULL,	NULL,   0,	0,     1 },
	{ "Emacs",     NULL,    NULL,   2,      0,     0 },
	{ "LibreWolf", NULL,    NULL,   1 << 4, 0,     0 },
	{ "Anki",      NULL,    NULL,   1 << 2, 0,     0 },
	{ "org.nicotine_plus.Nicotine", NULL, NULL, 1 << 5, 0, 0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[X]",      NULL },    /* no layout function means floating behavior */
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "[@]",      spiral },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmen", NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *term2cmd[] = { "st", NULL };
static const char *exitcmd[]  = { "pkill", "xinit", NULL };
static const char *toggleopacitycmd[] = { "toggle-opacity", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,		XK_Return, spawn,	   {.v = term2cmd } },
	{ MODKEY,                       XK_p,      togglebar,      {0} },
	{ MODKEY,                       XK_t,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_r,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_k,      setcfact,       {.f = +0.25} },
	{ MODKEY,                       XK_j,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY|ShiftMask,		XK_q,      spawn,	   {.v = exitcmd } },
	{ MODKEY|ShiftMask,		XK_g,	   spawn,	   {.v = toggleopacitycmd } },
	{ MODKEY,			XK_c,	   xrdb,           {.v = NULL } },
	/* dualshock commands */
	{ MODKEY,			XK_Prior,  shiftview,	   {.i = +1 } },
	{ MODKEY,			XK_Next,   shiftview,	   {.i = -1 } },
	{ MODKEY|ControlMask,		XK_Prior,  shift,	   {.i = +1 } },
	{ MODKEY|ControlMask,		XK_Next,   shift,	   {.i = -1 } },
	{ ControlMask,			XK_Prior,  focusstack,     {.i = -1 } },
	{ ControlMask,			XK_Next,   focusstack,     {.i = +1 } },
	{ MODKEY,			XK_Up,	   setcfact,	   {.f = +0.25} },
	{ MODKEY,			XK_Down,   setcfact,	   {.f = -0.25} },
	{ MODKEY,			XK_Left,   setmfact,	   {.f = -0.05} },
	{ MODKEY,			XK_Right,  setmfact,	   {.f = +0.05} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

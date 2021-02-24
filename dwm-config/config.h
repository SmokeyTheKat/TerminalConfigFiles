/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro Black:size=10" };
static const char dmenufont[]       = "Source Code Pro Black:size=10";
static const char col_yellow[]      = "#ffff00";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#232323";
static const char col_gray3[]       = "#555555";
static const char col_gray4[]       = "#eeeeee";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";
static const char col_blue[]        = "#0000c4";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_gray3 },
	[SchemeSel]  = { col_white, col_gray2,  col_white },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

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
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

void blankscreen(const Arg* args)
{
	system("xset s activate");
}

float _c_brightness[3] = { 1.0, 1.0, 1.0 };

void setbrightness(const Arg* args)
{
	_c_brightness[selmon->num] = args->f;
	char _lcommand[40];
	if (selmon->num == 0)
		strcpy(_lcommand, "xrandr --output 'DVI-I-0' --brightness ");
	if (selmon->num == 1)
		strcpy(_lcommand, "xrandr --output 'HDMI-0' --brightness  ");
	if (selmon->num == 2)
		strcpy(_lcommand, "xrandr --output 'DVI-D-0' --brightness ");
	int _lcommand_len = 40;
	char _fvalue[10];
	sprintf(_fvalue, "%f", _c_brightness[selmon->num]);
	int _fvalue_len = strlen(_fvalue);
	char* _fcommand = malloc(sizeof(char)*(_lcommand_len+_fvalue_len));
	strcpy(_fcommand, _lcommand);
	strcat(_fcommand, _fvalue);
	system(_fcommand);
	free(_fcommand);
}
void incbrightness(const Arg* args)
{
	_c_brightness[selmon->num] += args->f;
	char _lcommand[40];
	if (selmon->num == 0)
		strcpy(_lcommand, "xrandr --output 'DVI-I-0' --brightness ");
	if (selmon->num == 1)
		strcpy(_lcommand, "xrandr --output 'HDMI-0' --brightness  ");
	if (selmon->num == 2)
		strcpy(_lcommand, "xrandr --output 'DVI-D-0' --brightness ");
	int _lcommand_len = 40;
	char _fvalue[10];
	sprintf(_fvalue, "%f", _c_brightness[selmon->num]);
	int _fvalue_len = strlen(_fvalue);
	char* _fcommand = malloc(sizeof(char)*(_lcommand_len+_fvalue_len));
	strcpy(_fcommand, _lcommand);
	strcat(_fcommand, _fvalue);
	system(_fcommand);
	free(_fcommand);
}

void setcurfullscreen(const Arg* args)
{
	setfullscreen(selmon->sel, !(selmon->sel->isfullscreen));
}

void takescreenshot(const Arg* args)
{
	system("DXWDSS=$(date +%Y:%m:%d_%H:%M:%S) && xwd > ~/Pictures/SCREENSHOT_$(echo \"$DXWDSS\").xwd && convert ~/Pictures/SCREENSHOT_$(echo \"$DXWDSS\").xwd ~/Pictures/SCREENSHOT_$(echo \"$DXWDSS\").png && rm ~/Pictures/SCREENSHOT_$(echo \"$DXWDSS\").xwd && qview ~/Pictures/SCREENSHOT_$(echo \"$DXWDSS\").png &");
}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_white, "-sb", col_gray2, "-sf", col_white, NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *surfcmd[]  = { "konsole", "-e", "vifm", NULL };
static const char *volupcmd[]  = { "amixer", "sset", "'Master'", "10%+", NULL };
static const char *voldowncmd[]  = { "amixer", "sset", "'Master'", "10%-", NULL };

static Key keys[] = {
	/* modifier                     key            function           argument */
	{ MODKEY,                       XK_p,          spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,          takescreenshot,    {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,             {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_backslash,  spawn,             {.v = surfcmd } },
	{ MODKEY|ShiftMask,             XK_x,          blankscreen,       {.i = 0 } },
	{ MODKEY,                       XK_u,          spawn,             {.v = volupcmd } },
	{ MODKEY,                       XK_y,          spawn,             {.v = voldowncmd } },
	{ MODKEY|ShiftMask,             XK_r,          setbrightness,     {.f = 1.00f } },
	{ MODKEY|ShiftMask,             XK_e,          setbrightness,     {.f = 1.50f } },
	{ MODKEY,                       XK_r,          incbrightness,     {.f = 0.25f } },
	{ MODKEY,                       XK_e,          incbrightness,     {.f = -0.25f } },
	{ MODKEY,                       XK_b,          togglebar,         {0} },
	{ MODKEY,                       XK_j,          focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,          {.f = -0.025 } },
	{ MODKEY,                       XK_l,          setmfact,          {.f = +0.025 } },
	{ MODKEY,                       XK_Return,     zoom,              {0} },
	{ MODKEY,                       XK_Tab,        view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,        {0} },
	{ MODKEY,                       XK_f,          setcurfullscreen,  {.i = 0 } },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,    {0} },
	{ MODKEY,                       XK_comma,      focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,            {.i = +1 } },
	TAGKEYS(                        XK_1,                             0)
	TAGKEYS(                        XK_2,                             1)
	TAGKEYS(                        XK_3,                             2)
	TAGKEYS(                        XK_4,                             3)
	TAGKEYS(                        XK_5,                             4)
	TAGKEYS(                        XK_6,                             5)
	TAGKEYS(                        XK_7,                             6)
	TAGKEYS(                        XK_8,                             7)
	TAGKEYS(                        XK_9,                             8)
	TAGKEYS(                        XK_0,                             9)
	{ MODKEY|ShiftMask,             XK_q,          quit,              {0} },
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


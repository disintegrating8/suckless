/* appearance */
static const unsigned int refresh_rate        = 240;  /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder     = 1;   /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx            = 1;   /* border pixel of windows */
static const unsigned int snap                = 26;  /* snap pixel */
static const int swallowfloating              = 1;   /* 1 means swallow floating windows by default */
static const unsigned int systraypinning      = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft       = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing      = 5;   /* systray spacing */
static const int systraypinningfailfirst      = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray                  = 1;   /* 0 means no systray */
static const int showbar                      = 1;   /* 0 means no bar */
static const int topbar                       = 1;   /* 0 means bottom bar */
#define ICONSIZE                              17     /* icon size */
#define ICONSPACING                           5      /* space between icon and title */
#define SHOWWINICON                           1      /* 0 means no winicon */
static const char *fonts[]                    = { "MesloLGS Nerd Font Mono:size=16", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true" };
static const char normbordercolor[]           = "#3B4252";
static const char normbgcolor[]               = "#2E3440";
static const char normfgcolor[]               = "#D8DEE9";
static const char selbordercolor[]            = "#434C5E";
static const char selbgcolor[]                = "#434C5E";
static const char selfgcolor[]                = "#ECEFF4";

static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor },
};

static const char *const autostart[] = {
    "xrandr", "--output", "DisplayPort-0", "--mode", "2560x1440", "--rate", "240", NULL,
    "ibus-daemon", "-rxRd", NULL,
    "xset", "s", "off", NULL,
    "xset", "s", "noblank", NULL,
    "xset", "-dpms", NULL,
    "dbus-update-activation-environment", "--systemd", "--all", NULL,
    "/usr/lib/mate-polkit/polkit-mate-authentication-agent-1", NULL,
    "flameshot", NULL,
    "dunst", NULL,
    "picom", "-b", NULL,
    "sh", "-c", "feh --randomize --bg-fill ~/Pictures/backgrounds/*", NULL,
    "slstatus", NULL,
    "/bin/sh", "-c", "$HOME/suckless/initial-boot.sh", NULL,
    NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "", "", "󰊖", "", "" };

// static const char ptagf[] = "[%s %s]";  /* format of a tag label */
// static const char etagf[] = "[%s]";     /* format of an empty tag */
// static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const Rule rules[] = {
    /* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "St",                 NULL,     NULL,           0,         0,          1,          0,         -1 },
    { "kitty",              NULL,     NULL,           1 << 0,    0,          1,          0,         -1 },
    { "Brave-browser",      NULL,     NULL,           1 << 1,    0,          0,          0,         -1 },
    { "librewolf",          NULL,     NULL,           1 << 1,    0,          0,          0,         -1 },
    { "obs-studio",         NULL,     NULL,           1 << 3,    0,          0,          0,         -1 },
    { "lutris",             NULL,     NULL,           1 << 4,    1,          0,          0,         -1 },
    { "steam",  "steamwebhelper",     NULL,           1 << 4,    1,          0,          0,         -1 },
    { "PrismLauncher","prismlauncher",NULL,           1 << 4,    1,          0,          0,         -1 },
    { "discord",            NULL,     NULL,           1 << 6,    0,          0,          0,         -1 },
    { "vesktop",            NULL,     NULL,           1 << 6,    0,          0,          0,         -1 },
    { "signal",             NULL,     NULL,           1 << 6,    0,          0,          0,         -1 },
    { "steam_app_",         NULL,     NULL,           1 << 7,    1,          0,          0,         -1 },
    { "Minecraft",          NULL,     NULL,           1 << 7,    0,          0,          0,         -1 },
    { NULL,                 NULL,     "Event Tester", 0,         0,          0,          1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
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
#define STATUSBAR "dwmblocks"
/* commands */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]     = { "kitty", NULL };

static Key keys[] = {
    /* modifier                     key                        function        argument */

    // brightness and audio 
    { 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD ("xbacklight -inc 10")},
    { 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD ("xbacklight -dec 10")},
    { 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD ("pamixer -d 5")},
    { 0,                            XF86XK_AudioMute,          spawn,          SHCMD ("pamixer -t")},
    { 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD ("pamixer -i 5 --allow-boost --set-limit 150")},

    // screenshot
    { MODKEY,                       XK_p,                      spawn,          SHCMD ("flameshot full -p /media/drive/Screenshots/")},
    { MODKEY|ShiftMask,             XK_p,                      spawn,          SHCMD ("flameshot gui -p /media/drive/Screenshots/")},
    { MODKEY|ShiftMask,             XK_s,                      spawn,          SHCMD ("flameshot gui")},

    { MODKEY,                       XK_space,                  spawn,          {.v = launchercmd} },
    { MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
    { MODKEY|ControlMask,           XK_r,                      spawn,          SHCMD ("protonrestart")},
    { MODKEY,                       XK_b,                      spawn,          SHCMD ("xdg-open https://")},
    { MODKEY,                       XK_v,                      spawn,          SHCMD ("flatpak run com.discordapp.Discord")},
    { MODKEY,                       XK_e,                      spawn,          SHCMD ("xdg-open .")},
    { MODKEY,                       XK_w,                      spawn,          SHCMD ("looking-glass-client -F")},
    { MODKEY|ShiftMask,             XK_w,                      spawn,          SHCMD ("feh --randomize --bg-fill ~/Pictures/backgrounds/*")},

    // toggle stuff
    { MODKEY|ShiftMask,             XK_b,                      togglebar,      {0} },
    { MODKEY|ShiftMask,             XK_m,                      togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_y,                      togglefakefullscreen, {0} },

    { MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,                      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,                      movestack,      {.i = -1 } },
    { MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },

    { MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,                      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,                      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,                      setcfact,       {.f =  0.00} },


    { MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
    { MODKEY,                       XK_Tab,                    view,           {0} },

    { MODKEY,                       XK_q,                      killclient,     {0} },
    { MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                      fullscreen,     {0} },
    { MODKEY,                       XK_r,                  setlayout,      {0} },
    { MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
    { MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,                      quit,           {0} },
    { MODKEY|ControlMask,           XK_q,                      spawn,          SHCMD("$HOME/.config/rofi/powermenu.sh")},
    { MODKEY|ControlMask|ShiftMask, XK_r,                      spawn,          SHCMD("systemctl reboot")},
    { MODKEY|ControlMask|ShiftMask, XK_s,                      spawn,          SHCMD("systemctl suspend")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

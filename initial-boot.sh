#!/bin/bash

scriptsDir=$HOME/.config/hypr/scripts
wallpaper=$HOME/.config/hypr/wallpaper_effects/.wallpaper_current
waybar_style="$HOME/.config/waybar/style/[Extra] Modern-Combined - Transparent.css"
kvantum_theme="catppuccin-mocha-blue"
color_scheme="prefer-dark"
gtk_theme="Flat-Remix-GTK-Blue-Dark"
icon_theme="Flat-Remix-Blue-Dark"
cursor_theme="Bibata-Modern-Ice"

swww="swww img"
effect="--transition-bezier .43,1.19,1,.4 --transition-fps 30 --transition-type grow --transition-pos 0.925,0.977 --transition-duration 2"

# Check if a marker file exists.
if [ ! -f "$HOME/suckless/.initial_startup_done" ]; then
    # initiate GTK dark mode and apply icon and cursor theme
    gsettings set org.gnome.desktop.interface color-scheme $color_scheme > /dev/null 2>&1 &
    gsettings set org.gnome.desktop.interface gtk-theme $gtk_theme > /dev/null 2>&1 &
    gsettings set org.gnome.desktop.interface icon-theme $icon_theme > /dev/null 2>&1 &
    gsettings set org.gnome.desktop.interface cursor-theme $cursor_theme > /dev/null 2>&1 &
    gsettings set org.gnome.desktop.interface cursor-size 24 > /dev/null 2>&1 &

    # initiate kvantum theme
    kvantummanager --set "$kvantum_theme" > /dev/null 2>&1 &

    # Create a marker file to indicate that the script has been executed.
    touch "$HOME/suckless/.initial_startup_done"

    exit
fi

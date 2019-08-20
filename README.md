# ukui-panel  
## Overview
`ukui-panel` represents the taskbar of UKUi.
The elements available in lxqt-panel are called "plugin" technically. This applies e. g. to the source code where they reside in directories `./plugin-<plugin>` like `plugin-mainmenu`. In contrast to this they are called "widgets" by the configuration GUI so far. Also, a more descriptive term is used to refer to distinct plugins within the GUI. E. g. the aforementioned `plugin-mainmenu` is called "Application menu" that way.
Configuration dialogue "Add Plugins", , is listing all available plugins plus a short description and hence provides an overview of the available ones.
Notes on some of the plugins, sorted by terms used within the GUI in alphabetical order, technical term in parenthesis:

## Installation
### Compiling source code
The runtime dependencies are libxcomposite, libdbusmenu-qt5, KGuiAddons, KWindowSystem, Solid, menu-cache, lxmenu-data, [liblxqt] and [lxqt-globalkeys].
Several plugins or features thereof are optional and need additional runtime dependencies. Namely these are (plugin / feature in parenthesis) Alsa library (Alsa support in plugin-volume), PulseAudio client library (PulseAudio support in plugin-volume), lm-sensors (plugin-sensors), libstatgrab (plugin-cpuload, plugin-networkmonitor), [libsysstat] (plugin-sysstat).
Code configuration is handled by qMake. 
By default all available plugins and features thereof are built and qMake fails when dependencies aren't met. Building particular plugins can be disabled by boolean CMake variables `<plugin>_PLUGIN` where the plugin is referred by its technical term like e. g. in `SYSSTAT_PLUGIN`. Alsa and PulseAudio support in plugin-volume can be disabled by boolean varia

To build run `make`, to install `make install` which accepts variable `DESTDIR` as usual.

## Configuration, Usage

### Customizing

To customize the panel itself there's a context menu, that is a menu opened by right-clicking the pointer device. It is comprising sections "\<plugin\>" and "Panel" which allow for configuring the plugin the pointer is currently over and the panel as a whole respectively.

In section "Panel" topics "Configure Panel" and "Manage Widgets" open different panes of a dialogue "Configure Panel" which allow for configuring the panel as a whole and the various plugins respectively.
Pane "Widgets" allows for configuring and removing all plugins currently included in ukui-panel. The plus sign opens another dialogue "Add plugins" which is used to add plugins. It comes with a list of all plugins plus some short descriptions and can hence serve as overview what plugins are available.

Sometimes right-clicking over particular plugins may bring up a context menu dealing with the respective plugin's functionality *only* which means the plugin in question cannot be configured the usual way. This affects e. g. plugin-quicklaunch as soon as items were added (the context menu is limited to topics dealing with the items included in plugin-quicklaunch).
Currently there are two ways to deal with this. Some themes like e. g. `Frost` come with handles at the plugins' left end providing the regular context menu. Also, it can be assumed at least one plugin is included in the panel that's always featuring the regular context menu like e. g. plugin-mainmenu. Either way pane "Widgets" of "Configure Panel" can be accessed and used to configure the particular plugin

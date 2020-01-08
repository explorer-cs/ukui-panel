[ -f /home/kylin/work/ukui-panel/plugin-mount/resources/mount.desktop.in ] || exit 0
echo '[lxqt.mount_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = plugin-mount/resources/mount.desktop.in'
echo 'file_filter = plugin-mount/translations/mount_<lang>.desktop'
echo ''

./create_remap -f "/<artist>/<album>/<track>. <title>.<type>" \
"remap_test_cases.txt" \
"mkdir -p \"/home/brian/tmp/<artist>/<album>/\" & \
lame --preset medium \"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.<type>\" \"/home/brian/tmp/<artist>/<album>/<track>: <artist>-<album>-<title>.<type>\""\
> copy.sh

--RUN IT?
#chmod +x copy.sh
#./copy.sh
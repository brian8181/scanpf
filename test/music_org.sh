// REMAP FLAC ONLY

./scanpf -f "/<artist>/<album>/<track>. <title>.<type>" \
"remap_test_cases.txt" \
"mkdir -p \"/home/brian/tmp/<artist>/<album>/\" & \
lame --preset medium \"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.flac\" \"/home/brian/tmp/<artist>/<album>/<track>. <artist>-<album>-<title>.mp3\""\
> copy.sh

--RUN IT?
#chmod +x copy.sh
#./copy.sh


    ./scanpf -f "\"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.flac\"" "\"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<track>. <title>.flac\"" "/home/brian/tmp/flac-test.txt"

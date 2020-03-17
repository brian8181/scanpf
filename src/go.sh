#test
./scanpf "<a>.<c>.<b>" \
"<b>.<c>.<a>" \
"A.B.C"

#find '/media/brian/TOSHIBA EXT/music/albums/' -iname '*.flac' > flac_list.txt

./scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent Sequence.flac"

#output
#media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent Sequence.flac


./scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.01. Heart Beat, Pig Meat Soundtrack Ver.flac"

#output
#/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.01. Heart Beat, Pig Meat Soundtrack Ver.flac

./scanpf "1970 - The Ultimate Zabriskie Point/<N>.flac" \
"1970 - The Ultimate Zabriskie Point/<N>.flac" \
"1970 - The Ultimate Zabriskie Point/TMP.flac"

#output
#1970 - The Ultimate Zabriskie Point/TMP.flac

./scanpf "/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/Pink Floyd/1970 - The Ultimate Zabriskie Point/TMP.flac"

#output
#/Pink Floyd/1970 - The Ultimate Zabriskie Point/TMP.flac


./scanpf "/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
"/Pink Floyd/1970 - The Ultimate Zabriskie Point/TMP.flac"

#output
#/Pink Floyd/1970 - The Ultimate Zabriskie Point/TMP.flac







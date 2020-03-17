# # START TEST
# ../src/scanpf "<a>.<c>.<b>" \
# "<b>.<c>.<a>" \
# "A.B.C"

# #Expected Output:
# #C.B.A

# #"06. Señor (Tales of Yankee Power).flac"

# ..

# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent Sequence.flac"

# #output
# #media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent Sequence.flac

# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent & Sequence.flac"

# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/1.10. The Violent % Sequence.flac"

# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/1970 - The Ultimate Zabriskie Point/06. Señor (Tales of Yankee Power).flac"

# echo
# echo "***********************************************************"
# echo "*********************** SAMPLE TEST ***********************"
# echo "***********************************************************"
# echo 

# ../src/scanpf -f "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/<album>/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Pink Floyd/<album>/<N>.flac" \
# "flac_sample_debug.txt"

#output correct

echo
echo "***********************************************************"
echo "***********************    TEST     ***********************"
echo "***********************************************************"
echo 

../src/scanpf -f "/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<filename>.<type>" \
"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<filename>.flac" \
"flac_list.txt" > DEBUG_OUTPUT.txt


echo
echo "***********************************************************"
echo "***********************    TEST2    ***********************"
echo "***********************************************************"
echo 

../src/scanpf -f "/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<fullname>" \
"/media/brian/TOSHIBA EXT/music/albums/<artist>/<album>/<fullname>" \
"flac_list.txt" > DEBUG_OUTPUT_MATCH.txt


#/media/brian/TOSHIBA EXT/music/albums/Ian Dury/2005 - Reasons to Be Cheerful the Best of Ian Dury/2.flac
#/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/01.flac

# #NO
# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/<N>.<type>" \
# "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/<N>.flac" \
# "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/01. minipops 67 [120.2][source field mix].flac"

# #YES
# ../src/scanpf "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/<N>.<type>" \
# "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/<N>.<type>" \
# "/media/brian/TOSHIBA EXT/music/albums/Aphex Twin/2014 - Syro/01. minipops 67 [120.2][source field mix].flac"









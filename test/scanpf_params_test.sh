BUILD="../build"


$BUILD/scanpf "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 

echo
echo "Missing Paramaters ..."
echo

$BUILD/scanpf "<A>.<B>.<C>" "<C>.<B>.<A>" 
$BUILD/scanpf "<A>.<B>.<C>" 

echo
echo "Verbose Option ..."
echo

$BUILD/scanpf -v "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 

echo
echo "Help Option ..."
echo 

$BUILD/scanpf -h
$BUILD/scanpf -hv "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 
$BUILD/scanpf -vh "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 
$BUILD/scanpf -hv "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 
$BUILD/scanpf -vh "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 
$BUILD/scanpf -h -v "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 
$BUILD/scanpf -v -h "<A>.<B>.<C>" "<C>.<B>.<A>" "A.B.C" 


#09: Bob Dylan - 1965 - Highway 61 Revisited - Desolation Row.mp3
TEST_FILE="remap_test_case_file_names.txt"
$BUILD/scanpf -f "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -fv "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -vf "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -f -v "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -v -f "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE

$BUILD/scanpf -hf "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -fh "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -f -h "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -h -f "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -hf "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -fh "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -hfv "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -vhf "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -h -f -v "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
$BUILD/scanpf -v -h -f "<track>: <artist> - <date> - <album> - <title>.<ext>" "/<artist>/<date> - <ablbum>/<track>. <title>.<ext>" $TEST_FILE
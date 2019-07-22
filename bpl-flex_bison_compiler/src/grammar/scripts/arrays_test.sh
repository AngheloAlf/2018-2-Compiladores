DIRECTORY=../../../tests

array=("arrays.bpl" "queens.bpl" "sort.bpl")

clear
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

make
rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

printf "\n"
for i in "${array[@]}"; do
    printf "processing: "
    printf $i
    printf "\n"

    printf "generate asm\n"
    printf "./grammar.out $DIRECTORY/$i $DIRECTORY/$i.s\n"
    ./../out/grammar.out $DIRECTORY/$i $DIRECTORY/$i.s
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf "Building\n"
    printf "gcc $DIRECTORY/$i.s -o $DIRECTORY/$i.out\n"
    gcc $DIRECTORY/$i.s -o $DIRECTORY/$i.out  -L../out/ -lbplstd
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf "executing\n"
    printf "./$DIRECTORY/$i.out\n"
    ./$DIRECTORY/$i.out
    # rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf "\n"
done

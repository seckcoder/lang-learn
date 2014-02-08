FILEDIR=${FILEDIR:-"./"}
JSFILES=${JSFILES:-test haha}
TARGET=${TARGET:-tmp.js}

echo > $TARGET

for f in $JSFILES
do
    CURFILE="$FILEDIR/$f.js"
    if [[ ! (-e $CURFILE)]]; then
        echo "file $CURFILE not exist"
    else 
        echo "//$f.js" >> $TARGET
        cat $CURFILE >> $TARGET
        printf "\n\n" >> $TARGET
    fi
    #cat $FILEDIR/$f.js &> $TARGET
done

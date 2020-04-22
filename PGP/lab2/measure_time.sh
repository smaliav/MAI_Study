start=`date +%N`

./lab2 <image.txt

end=`date +%s`

let "res = (end - start) / 1000000"

echo $res

for file in tests/*
do

start=`date +%s%N`

./lab2 <$file

end=`date +%s%N`

let "res = (end - start) / 1000000"

echo $file $res

done

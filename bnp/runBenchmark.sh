make


k=1


for instance in instances/*; do
	
	echo "Processando $instance"
	echo "Instance $k of 68"
	echo $'\n' ${instance} >> ./t
	./bnp ${instance}
	
	k=$(($k+1))
done

echo "-" >> ./t

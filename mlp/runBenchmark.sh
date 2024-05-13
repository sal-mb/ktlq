make


k=1


echo "instancia - tempo custo" $'\n' >> ./output.txt

for instance in instances/*; do
	
	echo "Processando $instance"
	echo "Instance $k of 68"
	
	./mlp ${instance} >> ./output.txt
	
	k=$(($k+1))
done

echo "-" >> ./output.txt
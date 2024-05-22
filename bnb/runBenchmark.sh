make


k=1


echo "nome da instancia - branching (0 - dfs, 1 - bfs)"$'\n'"solucao"$'\n'"tempo - custo" >> ./benchmark.txt

for instance in instances/*; do
	
	echo "Processando $instance"
	echo "Instance $k of 68"
	
	./bnb ${instance} 0 >> ./benchmark.txt
	./bnb ${instance} 1 >> ./benchmark.txt

	k=$(($k+1))
done

echo "-" >> ./benchmark.txt
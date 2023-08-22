file_name="./tracefile/400_perlbench.out ./tracefile/450_soplex.out ./tracefile/453_povray.out ./tracefile/462_libquantum.out ./tracefile/473_astar.out ./tracefile/483_xalancbmk.out"
capacity=(256)
associativity=(4)
block_size=(16 32 64 128)
for f in $file_name
do
	echo file name is $f
	for c in "${capacity[@]}"
	do
		echo capacity is $c
		for a in "${associativity[@]}"
		do
			echo associativity is $a
			for b in "${block_size[@]}"
			do
				echo block_size is $b
				./runfile -c $c -a $a -b $b -random $f
			done
		done
	done
done

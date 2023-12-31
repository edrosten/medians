BEGIN{
	PROCINFO["sorted_in"] = "@ind_num_asc"
}
{
	num[$1]++
	sum[$1]+=$C
}

END{
	for(i in num)
		print i, sum[i]/num[i] / 1e9 * 1000
}

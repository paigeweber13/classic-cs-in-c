### A Pluto.jl notebook ###
# v0.14.7

using Markdown
using InteractiveUtils

# ╔═╡ d6a054e2-c7bf-11eb-3732-c3135a35f956
# load libraries

begin
	using CSV
	using DataFrames
	using Plots
end

# ╔═╡ 3b969425-8ee1-4bfd-af35-27238bf7ae7b
# load csv data
begin
	CSV_FILE_NAME = "results-2021-06-07_0842.csv"
	
	df = CSV.File(CSV_FILE_NAME, normalizenames=true) |> DataFrame
	df.status
end

# ╔═╡ Cell order:
# ╠═d6a054e2-c7bf-11eb-3732-c3135a35f956
# ╠═3b969425-8ee1-4bfd-af35-27238bf7ae7b

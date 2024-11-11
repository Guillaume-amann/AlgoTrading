(* Function to calculate the mean of a sample *)
let mean sample =
  let sum = List.fold_left ( +. ) 0.0 sample in
  sum /. (float_of_int (List.length sample))

(* Function to calculate the standard deviation of a sample *)
let standard_deviation sample =
  let m = mean sample in
  let variance =
    List.fold_left (fun acc x -> acc +. (x -. m) ** 2.0) 0.0 sample
    /. (float_of_int (List.length sample - 1))
  in
  sqrt variance

(* Function to calculate the t-statistic for a one-sample test *)
let one_sample_t_test sample population_mean =
  let sample_mean = mean sample in
  let sample_std_dev = standard_deviation sample in
  let n = float_of_int (List.length sample) in
  (sample_mean -. population_mean) /. (sample_std_dev /. sqrt n)

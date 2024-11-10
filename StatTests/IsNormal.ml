let one_sample_t_test sample population_mean =
  (* Some logic to calculate the t-statistic for the sample *)
  let n = float_of_int (List.length sample) in
  let mean = List.fold_left (+.) 0. sample /. n in
  let variance = List.fold_left (fun acc x -> acc +. (x -. mean) ** 2.) 0. sample /. n in
  let standard_error = sqrt (variance /. n) in
  (mean -. population_mean) /. standard_error
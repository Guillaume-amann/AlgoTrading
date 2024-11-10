open IsNormal

let () =
  let sample = [10.0; 12.0; 9.0; 11.5; 10.5] in
  let population_mean = 10.0 in
  let t_statistic = one_sample_t_test sample population_mean in
  Printf.printf "The t-statistic for the sample is: %f\n" t_statistic
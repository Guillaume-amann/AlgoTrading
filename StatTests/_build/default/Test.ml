open Isnormal
open Printf

(* Main function to run the test *)
let () =
  let sample = [|10.0; 12.0; 9.0; 11.5; 10.5|] in
  let population_mean = mean (Array.to_list sample) in  (* Compute mean using the function *)
  let population_std_dev = standard_deviation (Array.to_list sample) in  (* Compute standard deviation using the function *)
  let t_statistic = one_sample_t_test (Array.to_list sample) 10. in

  printf "The t-statistic for the sample is: %f\n" t_statistic;
  printf "The population mean is: %f\n" population_mean;
  printf "The population standard deviation is: %f\n" population_std_dev;
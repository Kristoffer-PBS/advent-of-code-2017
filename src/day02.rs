use crate::prelude::*;

// -----------------------------------------------------------------------------
// Part 1
// -----------------------------------------------------------------------------
fn part_1(input: &str) -> usize {
    input.lines().fold(0, |sum, line| {
        let row: Vec<usize> = line
            .split_whitespace()
            .map(|entry| entry.parse::<usize>().expect("Could not parse number"))
            .collect();
        let min = row.iter().min().unwrap();
        let max = row.iter().max().unwrap();
        sum + *max - *min
    })
}

fn is_evenly_divisible(a: usize, b: usize) -> Option<usize> {
    if a >= b {
        if a % b == 0 {
            return Some(a / b);
        }
    } else {
        if b % a == 0 {
            return Some(b / a);
        }
    }
    None
}

// -----------------------------------------------------------------------------
// Part 2
// -----------------------------------------------------------------------------
fn part_2(input: &str) -> usize {
    input.lines().fold(0, |sum, line| {
        let row: Vec<usize> = line
            .split_whitespace()
            .map(|entry| entry.parse::<usize>().expect("Could not parse number"))
            .collect();

        for i in 0..row.len() {
            for j in i + 1..row.len() {
                if let Some(division) = is_evenly_divisible(row[i], row[j]) {
                    return sum + division;
                }
            }
        }

        sum
    })
}

// -----------------------------------------------------------------------------
// Run
// -----------------------------------------------------------------------------
pub(crate) fn run() -> Results {
    // -------------------------------------------------------------------------
    // Setup
    // -------------------------------------------------------------------------
    let start_setup = Instant::now();
    let input = std::fs::read_to_string("input/day02.txt").expect("Could not open day02.txt");
    let time_setup = start_setup.elapsed();

    // -------------------------------------------------------------------------
    // Part 1
    // -------------------------------------------------------------------------
    let start_part_1 = Instant::now();
    let part_1 = part_1(&input);
    let time_part_1 = start_part_1.elapsed();

    // -------------------------------------------------------------------------
    // Part 2
    // -------------------------------------------------------------------------
    let start_part_2 = Instant::now();
    let part_2 = part_2(&input);
    let time_part_2 = start_part_2.elapsed();

    // -------------------------------------------------------------------------
    // Return
    // -------------------------------------------------------------------------
    Results::new(
        part_1 as i64,
        part_2 as i64,
        Timing::new(
            time_setup,
            time_part_1,
            time_part_2,
            time_setup + time_part_1 + time_part_2,
        ),
    )
}

// -----------------------------------------------------------------------------
// Report
// -----------------------------------------------------------------------------
pub(crate) fn report(results: &Results) {
    output::print_day(2);
    output::print_part(1, "sum", &format!("{}", results.part_1));
    output::print_part(2, "sum", &format!("{}", results.part_2));
    output::print_timing(&results.times);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn is_evenly_divisible_equal_input() {
        assert_eq!(is_evenly_divisible(10, 10), Some(1));
    }

    #[test]
    fn is_evenly_divisible_should_return_true() {
        assert_eq!(is_evenly_divisible(12, 6), Some(2));
    }

    #[test]
    fn is_evenly_divisible_should_return_false() {
        assert_eq!(is_evenly_divisible(7, 9), None);
    }

    #[test]
    fn part_1_example() {
        let input = ["5 1 9 5", "7 5 3", "2 4 6 8"].join("\n");
        assert_eq!(part_1(&input), 8 + 4 + 6);
    }

    #[test]
    fn part_2_example() {
        let input = ["5 9 2 8", "9 4 7 3", "3 8 6 5"].join("\n");
        assert_eq!(part_2(&input), 4 + 3 + 2);
    }
}

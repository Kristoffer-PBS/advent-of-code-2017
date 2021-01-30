fn main() {
    let input = std::fs::read_to_string("input/input.txt").unwrap();

    println!("PART 1: {}", part_1(&input));
    println!("PART 2: {}", part_2(&input));
}

fn part_1(input: &str) -> usize {
    let mut tape = input
        .lines()
        .map(|line| line.parse::<i32>().unwrap())
        .collect::<Vec<_>>();

    let mut idx = 0_i32;
    let mut count = 0_usize;

    while (idx as usize) < tape.len() {
        count += 1;
        let i = idx;
        idx += tape[idx as usize];
        tape[i as usize] += 1;
    }

    count
}

fn part_2(input: &str) -> usize {
    let mut tape = input
        .lines()
        .map(|line| line.parse::<i32>().unwrap())
        .collect::<Vec<_>>();

    let mut idx: i32 = 0;
    let mut count: usize = 0;

    loop {
        if idx as usize >= tape.len() {
            break count;
        }

        count += 1;
        let i = idx;
        idx += tape[idx as usize];
        if tape[i as usize] >= 3 {
            tape[i as usize] -= 1;
        } else {
            tape[i as usize] += 1;
        }
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn part_1_example() {
        let input = ["0", "3", "0", "1", "-3"].join("\n");
        assert_eq!(part_1(&input), 5);
    }

    #[test]
    fn part_2_example() {
        let input = ["0", "3", "0", "1", "-3"].join("\n");
        assert_eq!(part_2(&input), 10);
    }
}

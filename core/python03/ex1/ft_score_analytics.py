import sys

def calculate_stats(scores):
    total = sum(scores)
    count = len(scores)
    avg = total / count
    maximum = max(scores)
    minimum = min(scores)
    scores_range = maximum - minimum
    print(f"Scores processed: {scores}")
    print(f"Total players: {count}")
    print(f"Total score: {total}")
    print(f"Average score: {avg}")
    print(f"High score: {maximum}")
    print(f"Low score: {minimum}")
    print(f"Score range: {scores_range}")

def main()->None:
    args = sys.argv[1:]
    scores = []
    invalid_args = []

    print("=== Player Score Analytics ===")

    for item in args:
        try:
            scores.append(int(item))
        except ValueError:
            invalid_args.append(item)

    if len(scores) > 0:
        print("Scores processed: ")


    if not args:
        print("No scores provided. Usage: python3 ft_score_analytics.py <score1> <score2> ...")

    elif not scores:
        for item in invalid_args:
            print(f"Invalid parameter: '{item}'")
        print("No scores provided. Usage: python3 ft_score_analytics.py <score1> <score2> ...")

    else:
        for item in invalid_args:
            print(f"Invalid parameter: '{item}'")
        calculate_stats(scores)

if __name__ == "__main__":
    main()

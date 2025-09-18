import csv
import sys
import matplotlib.pyplot as plt

SUBTYPE_NAME = {
    2:  "msc",
    10: "eIoni",
    11: "eBrem",
    12: "photoelectric",
    13: "compton",
    14: "conversion",
    21: "ionIoni",
    22: "hIoni",
}

def read_csv(path):
    zbin, subtype, count = [], [], []
    with open(path, newline='') as f:
        r = csv.DictReader(f)
        for row in r:
            zbin.append(int(row["zbin"]))
            subtype.append(int(row["subtype"]))
            count.append(int(row["count"]))
        return zbin, subtype, count

def main():
    path = "dominant_by_depth.csv" if len(sys.argv) <2 else sys.argv[1]
    zbin, subtype, count = read_csv(path)

    plt.figure()
    plt.bar(zbin, count)
    for x, y, st in zip(zbin, count, subtype):
        name = SUBTYPE_NAME.get(st,str(st))
        plt.text(x,y,name, ha="center", va="bottom", rotation=90, fontsize=8)
    plt.xlabel("Depth bin (zbin)")
    plt.ylabel("Count (dominant process occurrences)")
    plt.title("Dominant process per depth bin (counts)")
    plt.tight_layout()
    plt.savefig("dominant_counts_by_depth.png", dpi=200)

    plt.figure()
    plt.plot(zbin,subtype, marker="o")
    plt.xlabel("Depth bin (zbin)")
    plt.ylabel("Dominant process subtype")
    plt.title("Dominant process subtype vs depth bin")
    plt.tight_layout()
    plt.savefig("dominant_subtype_by_depth.png", dpi=200)
    print("Saved: dominant_counts_by_depth.png, dominant_subtype_by_depth.png")

if __name__ == "__main__":
    main()

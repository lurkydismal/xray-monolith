#!/usr/bin/env python3

import pathlib

from lxml import etree as ET
from tqdm import tqdm


XML_DIR = pathlib.Path("doxygen/xml")

KINDS = {"function", "class", "struct", "variable"}


def has_documentation(member: ET._Element) -> bool:
    for tag in ("briefdescription", "detaileddescription"):
        node = member.find(tag)

        if node is not None and "".join(node.itertext()).strip():
            return True

    return False


def main() -> None:
    files = [file for file in XML_DIR.glob("*.xml") if file.name != "index.xml"]

    total = 0
    documented = 0

    for file in tqdm(files, desc="Scanning XML files", unit="file"):
        root = ET.parse(file).getroot()

        for member in root.findall(".//memberdef"):
            if member.attrib.get("kind") not in KINDS:
                continue

            total += 1

            if has_documentation(member):
                documented += 1

    print()
    print(f"Documented: {documented}/{total}")

    if total:
        coverage = documented / total * 100
        print(f"Coverage: {coverage:.2f}%")


if __name__ == "__main__":
    main()

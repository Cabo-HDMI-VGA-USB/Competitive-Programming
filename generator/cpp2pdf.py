# Créditos ao TiagoDFS - https://github.com/Tiagosf00/Competitive-Programming
# Créditos ao Bruno_Vargas - https://github.com/BrunoVarg/Competitive-Programming

import os, subprocess
from dataclasses import dataclass
from functools import reduce
from typing import Callable

@dataclass(frozen=True)
class Content:
    title: str
    complexity: str
    description: str
    code: str


WIKI_PATH = "./wiki"
SEP = os.sep
NOTEBOOK_NAME = "notebook.tex"
TEMPLATE_PATH = "./generator/template.tex"
ICON_PATH = "./generator/unb.jpg"

def read_entire_file(file_name: str) -> str:
    content = ""
    with open(file_name, "r") as f:
        content = f.read()

    return content

def is_subject_folder(s: str) -> bool:
    return len(s) > len(WIKI_PATH + SEP)

def subject_folder_name_from_path(path: str) -> str:
    return path.split(SEP)[-1]

def get_first_occur(s: str, pred: Callable[[str], bool]) -> int:
    for i, c in enumerate(s):
        if pred(c):
            return i

    return -1

def metadata_from_source(metadata_name: str,source: str) -> str:
    def check_if_metadata(line: str) -> bool:
        clean_line = line.strip().lower()
        return clean_line[get_first_occur(
            clean_line, 
            lambda c: c != " " and c != "/"
        ):].startswith(metadata_name.lower())

    lines = [line for line in source.split("\n") if check_if_metadata(line)]
    metadata = (
            ":".join(lines[0].split(":")[1:]).strip()
            if len(lines) > 0
            else ""
    )
    return (
        metadata[get_first_occur(
            metadata, 
            lambda c: c != " " and c != "/"
        ):]
        if metadata
        else ""
    )


def string_to_content(source: str) -> Content:
    title = metadata_from_source("title", source)
    complexity = metadata_from_source("complexity", source)
    description = metadata_from_source("description", source)

    return Content(title=title, complexity=complexity, description=description, code=source)

def scape_string(source: str) -> str:
    return source.replace(r"_", r"\_")

def content_to_latex(content: Content) -> str:
    return f"""
\\subsection{{{scape_string(content.title)}}}
Complexity: {scape_string(content.complexity)} \\\\
{scape_string(content.description)}
\\begin{{lstlisting}}
{content.code}
\\end{{lstlisting}}
    """

def apply_content_to_latex_template(content: str, icon_path: str, template_path: str) -> str:
    return read_entire_file(template_path).replace("[[content]]", content).replace("[[icon-path]]", icon_path)

def write_to_file(content: str, file_path: str) -> None:
    with open(file_path, "w") as f:
        f.write(content)


def clean_latex_aux_files(tex_or_pdf_path: str) -> None:
    file_name = ".".join(tex_or_pdf_path.split(".")[:-1])
    items = [
        f"{file_name}.aux",
        f"{file_name}.log",
        f"{file_name}.toc",
        f"{file_name}.tex",
        'texput.log',
    ]
    for item in items:
        if os.path.exists(item):
            os.remove(item)

def compile_tex(tex_path: str) -> None:
    cmd = ['pdflatex', '-interaction=nonstopmode', '-halt-on-error',
           tex_path]
    with open(os.devnull, 'w') as DEVNULL:
        try:
            subprocess.check_call(cmd, stdout=DEVNULL)
            subprocess.check_call(cmd, stdout=DEVNULL)
        except Exception:
            print("Erro na transformação de LaTex para pdf.")
            print("Execute manualmente para entender o erro:")
            print(f"pdflatex -interaction=nonstopmode -halt-on-error {tex_path}")
            exit(1)

    clean_latex_aux_files(tex_path)
    print("O PDF foi gerado com sucesso!")

def main() -> None:
    files = [
        (subject_folder_name_from_path(dirpath), [os.path.join(dirpath, file) 
                                                  for file in filenames]) 
        for dirpath, _, filenames in os.walk(WIKI_PATH) 
        if is_subject_folder(dirpath)
    ]
    subjects = [
            (subject_folder.capitalize(), [
                    string_to_content(read_entire_file(source)) for source in sources
                ]) 
            for subject_folder, sources in files
    ]
    content_in_latex_list = [
            (subject, reduce(
                lambda str1, str2: str1 + "\n" + str2,
                [content_to_latex(content) for content in contents]
            ))
            for subject, contents in subjects
    ]
    content_in_latex = reduce(
            lambda str1, str2: str1 + "\n" + f"\\section{{{str2[0]}}}\n" + str2[1], 
            content_in_latex_list,
            ""
    )

    full_latex = apply_content_to_latex_template(content_in_latex, ICON_PATH, TEMPLATE_PATH)
    write_to_file(full_latex, NOTEBOOK_NAME)
    compile_tex(NOTEBOOK_NAME)

if __name__ == "__main__":
    main()

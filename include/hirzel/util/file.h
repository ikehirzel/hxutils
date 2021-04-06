#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <vector>
#include <string>
#include <cstdio>

namespace hirzel
{
	namespace file
	{
		std::vector<std::string> read_file_as_vector(const std::string& filename);
		std::string read_file_as_string(const std::string& filename, bool ignore_empty_lines = false,
			const std::string& line_ending_fmt = "\n");
		std::vector<std::vector<std::string>> read_csv(const std::string& filename);
		void write_file(const std::string& filename, const std::string& buf);
		bool file_exists(const std::string& filepath);
	}
}

#endif // UTIL_FILE_H

#ifdef HIRZEL_UTIL_FILE_I
#undef HIRZEL_UTIL_FILE_I

#include <fstream>

namespace hirzel
{
	namespace file
	{
		std::vector<std::string> read_file_as_vector(const std::string &filename)
		{
			std::string line;
			std::vector<std::string> lines;
			std::ifstream fin(filename);

			if (fin.is_open())
			{
				while (std::getline(fin, line))
				{
					if (line.empty())
					{
						continue;
					}
					if (line.back() == '\r')
					{
						line.resize(line.size() - 1);
					}
					lines.push_back(line);
				}
				fin.close();
			}

			return lines;
		}

		std::string read_file_as_string(const std::string &filename, bool ignore_empty_lines,
			const std::string &line_ending_fmt)
		{
			std::string text, line;
			std::ifstream fin(filename);

			if (fin.is_open())
			{
				while (std::getline(fin, line))
				{
					if (line.empty() && ignore_empty_lines)
					{
						continue;
					}

					while (line.back() == '\r' || line.back() == '\n')
					{
						line.pop_back();
					}

					text += line + line_ending_fmt;
				}

				fin.close();
			}

			return text;
		}

		std::vector<std::vector<std::string>> read_csv(const std::string &filename)
		{
			std::vector<std::string> lines = read_file_as_vector(filename);
			std::vector<std::vector<std::string>> tokens;

			for (std::string str : lines)
			{
				tokens.push_back(str::tokenize(str, ",", false, false));
			}
			return tokens;
		}

		void write_file(const std::string &filename, const std::string &buf)
		{
			std::ofstream file;
			file.open(filename);
			file << buf;
			file.close();
		}

		bool file_exists(const std::string &filepath)
		{
			std::ifstream file(filepath);
			return file.good();
		}
	} // namespace file
} // namespace hirzel

#endif // HIRZEL_UTIL_FILE_I
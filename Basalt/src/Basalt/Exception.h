#pragma once

#include <exception>

namespace Basalt
{
	class Exception : public std::exception
	{
	public:
		/// <summary>
		/// Creates a generic exception
		/// </summary>
		/// <param name="line">The line number where the exception occurred</param>
		/// <param name="file">The file where the exception occurred</param>
		Exception(int line, String file);
		/// <summary>
		/// Returns the description of the exception and the type
		/// </summary>
		/// <returns>A description of the exception</returns>
		virtual String GetException() const;
		/// <summary>
		/// Returns the type of exception
		/// </summary>
		/// <returns>a string description of the type of exception</returns>
		virtual String GetType() const;
		/// <summary>
		/// Returns the line number where the exception occurred
		/// </summary>
		/// <returns>the line number of the exception</returns>
		int GetLine() const;
		/// <summary>
		/// Returns the file name where the exception occurred
		/// </summary>
		/// <returns>The file name of the exception</returns>
		String GetFile() const;
		/// <summary>
		/// Returns a formatted string with the file name and line number
		/// </summary>
		/// <returns>Formatted string indicating where the exception occurred</returns>
		String GetOriginString() const;
	private:
		const char* what() const override;

	protected:
		mutable std::string whatBuffer;
	private:
		int line;
		String file;
	};
}

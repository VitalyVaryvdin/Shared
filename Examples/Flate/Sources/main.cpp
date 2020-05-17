#include "System.h"

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "puff.h"

// int MaxCompressedSize(int SrcLen)
// {
// 	int n16kBlocks = (SrcLen + 16383) / 16384; // round up any fraction of a block
// 	return (SrcLen + 6 + (n16kBlocks * 5));
// }

int main(int argc, char** argv)
{
	std::ofstream headerInfo;
	File bin(argv[1]);

	std::string fileNameDump;
	std::string fileNameHeader;
	std::string fileNameHeaderInfo;

	fileNameDump += GetPath(argv[1]);		// full path to the file	C:\Program files\APBAssetsDumper\Data
	fileNameDump += "APBAssetsDumper\\";	// our output directyro		C:\Program files\APBAssetsDumper\Data\APBAssetsDumper
	fileNameDump += GetFileName(argv[1]);	// our input file filename	C:\Program files\APBAssetsDumper\Data\APBAssetsDumper\InputFile.bin

	FileSystem::CreateDirectoryTreeFromPath(fileNameDump.c_str()); // creates directory tree of path from above

	fileNameDump += "\\";					/* add slash to the path	C:\Program files\APBAssetsDumper\Data\APBAssetsDumper\InputFile.bin\ */
	fileNameDump += GetFileName(argv[1]);	/* add resulting file name	C:\Program files\APBAssetsDumper\Data\APBAssetsDumper\InputFile.bin\InputFile.bin */

	fileNameHeader += fileNameDump;
	fileNameHeader += ".header";			/* add .header extension	C:\Program files\APBAssetsDumper\Data\APBAssetsDumper\InputFile.bin\InputFile.bin.header */
	
	fileNameHeaderInfo += fileNameDump;
	fileNameHeaderInfo += "_header";
	fileNameHeaderInfo += ".txt";

	fileNameDump += ".dump";				/* add .dump extension		C:\Program files\APBAssetsDumper\Data\APBAssetsDumper\InputFile.bin\InputFile.bin.dump */

	bin.ReadU16();
	bin.ReadU16();
	int uncompressedSize =  bin.ReadU16();
	
	bin.Seek(0, Stream::Begin);

	Buffer header(0x2e);
	header.Write(bin.ReadRaw(0x2e), 0x2e);

	bin.Seek(0x2e, Stream::Begin);

	if(!bin.IsOpened())
		return 1;

	Buffer compressed(bin.Size());
	Buffer uncompressed(uncompressedSize);
	compressed.Write(bin.ReadRaw(bin.Size()), bin.Size());

	unsigned long destLen = (unsigned long)uncompressed.Capacity();
	unsigned long srcLen = (unsigned long)compressed.Size();

	puff((unsigned char*)uncompressed.Data(), &destLen, (unsigned char*)compressed.Data(), &srcLen); // uncompress file data

	File dump(fileNameDump.c_str());
	dump.Write(header.Data(), 0x2e);
	dump.Write(uncompressed.Data(), (size_t)destLen);
}

/*int main(int argc, char** argv)
{
	HTTPFileDownloader fd;
	// declarations
	std::string InputFileName,
				OutputFileName;

	//fd.Download("http://www.gildor.org/down.php?file=35/umodel/umodel_win32.zip", SplitFileNameFromPath("http://www.gildor.org/down/35/umodel/umodel_win32.zip"));

	File InputFile;
	File OutputFile;

	ZLIBCompressor Compressor;

	Timer::Start();

	int Flag = -1; // 0 - compress, 1 - decompress
	int Level = 5;

	if(argc == 1)
	{
		std::cout	<< "Usage: " << argv[0] << " <input file name> <out put file name> [options]\n"
					<< "Available options:\n"
					<< "\t-c\t\tcompress file\n"
					<< "\t-d\t\tdecompress file\n"
					<< "\t-l <level>\tcompression level, from 1(fastest) to 9(best)\n";

		return 0;
	}

	std::string ArgLog;

	// arguments parsing
	for(int i = 0; i < argc; i++)
	{
		if(!strcmp(argv[i], "-c"))
			Flag = 0;
		else if(!strcmp(argv[i], "-d"))
			Flag = 1;
		else if(!strcmp(argv[i], "-l"))
		{
			Level = atoi(argv[i + 1]);
		}

		ArgLog.append(argv[i]);
		ArgLog.append(" ");
	}

	Log::Output(Format("Starting.. command line: %s", ArgLog.c_str()));

	ArgLog.clear();

	InputFileName = argv[1];
	OutputFileName = argv[2];

	// file existence checking
	if(!FileSystem::IsExists(InputFileName.c_str()))
	{
		Log::Output("Input file was not found, exiting\n", Log::Error);
		return 1;
	}

	if(FileSystem::IsExists(OutputFileName.c_str()))
	{
		Log::Output("Output file already exists, exiting\n", Log::Error);
		return 1;
	}

	InputFile.Open(InputFileName.c_str());
	OutputFile.Open(OutputFileName.c_str());

	Log::Output(Format("Input file: %s\n", argv[1]));
	Log::Output(Format("Input file size: %i\n", InputFile.Size()));

	Buffer In;
	Buffer Out;

	int CompressedSize = 0;
	int UncompressedSize = 0;

	In.Resize(InputFile.Size());

#ifdef _DEBUG
	Log::Output(Format("Input buffer allocated memory: %i", In.Capacity()), Log::Warning);
#endif

	InputFile.WriteToBuffer(&In);

	// compressing/decompressing itself
	if(Flag == 0)
	{
		Out.Resize(MaxCompressedSize(InputFile.Size()));

#ifdef _DEBUG
		Log::Output(Format("Output buffer allocated memory: %i", Out.Capacity()), Log::Warning);
#endif

		Log::Output(Format("Compressing.. compression level choosen: %i\n", Level));

		CompressedSize = Compressor.Compress(Out.Data(), Out.Capacity(), In.Data(), In.Size(), Level);

		OutputFile.Write(Out.Data(), CompressedSize);

		Log::Output(Format("Output file: %s\n", argv[2]));
		Log::Output(Format("Output file size: %i\n", CompressedSize));

		Log::Output(Format("Compression ratio: %4.2f%%\n", (1.0 - OutputFile.Size() * 1.0 / InputFile.Size()) * 100.0));
	}
	else if(Flag == 1)
	{
		Out.Resize(InputFile.Size() * 5);

#ifdef _DEBUG
		Log::Output(Format("Output buffer allocated memory: %i", Out.Capacity()), Log::Warning);
#endif

		Log::Output("Decompressing..");

		UncompressedSize = Compressor.Decompress(Out.Data(), Out.Capacity(), In.Data(), In.Size());

		OutputFile.Write(Out.Data(), UncompressedSize);

		Log::Output(Format("Output file: %s\n", argv[2]));
		Log::Output(Format("Output file size: %i\n", UncompressedSize));

		Log::Output(Format("Decompression ratio: %4.2f%%\n", (1.0 - OutputFile.Size() * 1.0 / InputFile.Size()) * 100.0));
	}

	Timer::Stop();

	Log::Output(Format("Execution time: %f(ms)", Timer::GetTime()));

	return 0;
}*/
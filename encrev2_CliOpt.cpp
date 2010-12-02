#include <iostream>
#include <map>
#include <string>
#include "encrev2_CliOpt.hh"

VlcCliOpt::VlcCliOpt() : _opt() {}
VlcCliOpt::~VlcCliOpt() {}

void
VlcCliOpt::set_option(const std::string& global_option,
    const std::string& option,
    const std::string& value) {
	std::string key(global_option.c_str());
	key.append("-");
	key.append(option.c_str());
	std::clog << key << " - " << value << std::endl;
//	_opt[key] = value;
//	std::clog << "---->" << _opt[key] << std::endl;
}

/*
  Transcode stream output / Video conversion
*/
void
VlcCliOpt::initTranscode() {
	// Video transcode option
	_opt["transcode-venc"] = ""; // Video encoder - string
	_opt["transcode-vcodec"] = ""; // Video decoder - string
	_opt["transcode-vb"] = ""; // Target bitrate - integer
	_opt["transcode-scale"] = ""; // Scale factor - float
	_opt["transcode-fps"] = ""; // Target fps - float
	_opt["transcode-hurry-up"] = ""; //Transcoder will drop frame. Default enabled - bool
	_opt["transcode-deinterlace"] = "";// Default disable - bool
	_opt["transcode-width"] = ""; //Output video width - integer
	_opt["transcode-height"] = ""; //Output video height - integer
	_opt["transcode-maxwidth"] = "";
	_opt["transcode-maxheight"] = "";
	_opt["transcode-vfilter"] = "";
	// Audio transcode option
	_opt["transcode-aenc"] = "";
	_opt["transcode-acodec"] = "";
	_opt["transcode-ab"] = "";
	_opt["transcode-alang"] = ""; // Audio stream language
	_opt["transcode-channels"] = ""; // Number of audio channels
	_opt["transcode-samplerate"] = "";
	_opt["transcode-audio-sync"] = ""; // Aggressively force audio/video sync. - bool
	_opt["transcode-afilter"] = ""; //Audio filter
	_opt["transcode-ab"] = "";
	_opt["transcode-ab"] = "";
}

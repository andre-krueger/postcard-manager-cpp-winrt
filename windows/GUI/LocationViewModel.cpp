#include "pch.h"
#include "LocationViewModel.h"
#include "Location.h"

namespace winrt::GUI::implementation
{
	LocationViewModel::LocationViewModel()
	{
		auto locations = std::vector<winrt::GUI::Location>{
			winrt::make<GUI::implementation::Location>(L"Osten"),
			winrt::make<GUI::implementation::Location>(L"Hemmoor"),
			winrt::make<GUI::implementation::Location>(L"Hechthausen")
		};
		m_locations = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();

		for (auto &location : locations) {
			m_locations.Append(location);
		}
	}

	Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> LocationViewModel::Locations()
	{
		return m_locations;
	}
}

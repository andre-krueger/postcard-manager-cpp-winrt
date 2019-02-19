#include "pch.h"
#include "LocationView.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GUI::implementation
{
	LocationView::LocationView()
	{
		m_locationViewModel = winrt::make<GUI::implementation::LocationViewModel>();
		InitializeComponent();
	}

	GUI::LocationViewModel LocationView::LocationViewModel()
	{
		return m_locationViewModel;
	}
}

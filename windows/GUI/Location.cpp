#include "pch.h"
#include "Location.h"

namespace winrt::GUI::implementation
{
    Location::Location(hstring const & name) : m_name{ name }
    {
    }

    hstring Location::Name()
    {
        return m_name;
    }

    void Location::Name(hstring const& value)
    {
        if (m_name != value)
        {
            m_name = value;
            m_propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Name" });
        }
    }

    winrt::event_token Location::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }

    void Location::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
}

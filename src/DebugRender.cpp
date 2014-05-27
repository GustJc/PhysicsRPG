#include "DebugRender.h"
#include "Globals.h"
DebugRender::DebugRender(sf::RenderWindow* wnd)
{
    this->window = wnd;
}

DebugRender::~DebugRender()
{
    //dtor
}
/// Draw a closed polygon provided in CCW order.
void DebugRender::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    //cout << "DrawPolygon " << endl;
    sf::Vertex* vert = new sf::Vertex[vertexCount+1];
    for(int32 i = 0; i < vertexCount; ++i)
    {
        vert[i].position.x = vertices[i].x * pixelsPerMeter;
        vert[i].position.y = vertices[i].y * pixelsPerMeter;
        vert[i].color.r    = 255;
        vert[i].color.g    = 0;
        vert[i].color.b    = 0;
        vert[i].color.a    = 255;
        vert[i].texCoords.x = 0.0f;
        vert[i].texCoords.y = 0.0f;
    }
    vert[vertexCount] = vert[0];
    window->draw(vert, vertexCount+1, sf::LinesStrip);
    delete [] vert;
}

/// Draw a solid closed polygon provided in CCW order.
void DebugRender::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    //cout << "DrawSolidPolygon " << endl;
    sf::Vertex* vert = new sf::Vertex[vertexCount+1];
    for(int32 i = 0; i < vertexCount; ++i)
    {
        vert[i].position.x = vertices[i].x * pixelsPerMeter;
        vert[i].position.y = vertices[i].y * pixelsPerMeter;
        vert[i].color.r    = 255.f/color.r;
        vert[i].color.g    = 255.f/color.g;
        vert[i].color.b    = 255.f/color.b;
        vert[i].color.a    = 255;
        vert[i].texCoords.x = 0.0f;
        vert[i].texCoords.y = 0.0f;
    }
    vert[vertexCount] = vert[0];
    window->draw(vert, vertexCount+1, sf::LinesStrip);
    delete [] vert;
}

/// Draw a circle.
void DebugRender::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    cs.setPosition(center.x*pixelsPerMeter, center.y*pixelsPerMeter);
    cs.setRadius(radius*pixelsPerMeter);
    cs.setOutlineColor(sf::Color(color.r, color.g, color.b));
    window->draw(cs);
}

/// Draw a solid circle.
void DebugRender::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    cs.setFillColor(sf::Color(0,0,0,0));
    cs.setOutlineColor(sf::Color(255.f/color.r, 255.f/color.g, 255.f/color.b));
    cs.setOutlineThickness(2.f);
    cs.setPosition(center.x*pixelsPerMeter, center.y*pixelsPerMeter);
    cs.setRadius(radius*pixelsPerMeter);
    cs.setOrigin(radius*pixelsPerMeter, radius*pixelsPerMeter);
    window->draw(cs);

    b2Vec2 seg = center;
    seg.x += axis.x*radius;
    seg.y += axis.y*radius;
    DrawSegment(center, seg, color);
}

/// Draw a line segment.
void DebugRender::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    //cout << "DrawSegment " << endl;
    // 1.f = 255
    // 0.3f   = y
    sf::Vertex* vert = new sf::Vertex[2];
    vert[0].position.x = p1.x * pixelsPerMeter;
    vert[0].position.y = p1.y * pixelsPerMeter;
    vert[0].color.r    = 255.f/color.r;
    vert[0].color.g    = 255.f/color.g;
    vert[0].color.b    = 255.f/color.b;
    vert[0].color.a    = 255;
    vert[0].texCoords.x = 0.0f;
    vert[0].texCoords.y = 0.0f;

    vert[1].position.x = p2.x * pixelsPerMeter;
    vert[1].position.y = p2.y * pixelsPerMeter;
    vert[1].color.r    = 255.f/color.r;
    vert[1].color.g    = 255.f/color.g;
    vert[1].color.b    = 255.f/color.b;
    vert[1].color.a    = 255;
    vert[1].texCoords.x = 0.0f;
    vert[1].texCoords.y = 0.0f;

    window->draw(vert, 2, sf::Lines);
    delete [] vert;

}

/// Draw a transform. Choose your own length scale.
/// @param xf a transform.
void DebugRender::DrawTransform(const b2Transform& xf)
{
    //cout << "DrawTransform " << endl;
    b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;

	sf::Vertex* vert = new sf::Vertex[5];
	vert[0].position.x = p1.x * pixelsPerMeter;
    vert[0].position.y = p1.y * pixelsPerMeter;
    vert[0].color = sf::Color::Black;
	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	vert[1].position.x = p2.x * pixelsPerMeter;
    vert[1].position.y = p2.y * pixelsPerMeter;
    vert[1].color = sf::Color::Black;
    vert[2].position.x = p1.x * pixelsPerMeter;
    vert[2].position.y = p1.y * pixelsPerMeter;
    vert[2].color = sf::Color::Black;
	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	vert[3].position.x = p2.x * pixelsPerMeter;
    vert[3].position.y = p2.y * pixelsPerMeter;
    vert[3].color = sf::Color::Black;

    vert[4] = vert[0];
    window->draw(vert, 5, sf::LinesStrip);
    delete [] vert;

}
